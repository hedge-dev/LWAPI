#pragma once

namespace app
{
	class CActivationManager;
	typedef size_t CSetObjectID;

	namespace SetEd
	{
		class CResource : public fnd::ReferencedObject
		{
			INSERT_PADDING(32);
		};
	}

	struct SLayerInfo
	{
		csl::ut::Bitset<uint> m_Flags;
		void* m_Unk1;
		csl::ut::FixedString<64> m_Name;
	};

	class CSetObjectManager : public fnd::GameService
	{
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEF2E8));
	protected:
		GameDocument* m_pDocument;
		INSERT_PADDING(8); // boost::shared_ptr<app::CSetObjectFactory>
		csl::ut::LinkList<CSetObjectListener> m_Objects;
		SLayerInfo m_Layers[9];
		size_t m_CurrentLayerIdx;
		CLevelInfo* m_pLevelInfo;
		CActivationManager* m_pActivationMan;
		app::ut::RefPtr<SetEd::CResource> m_rpRes;
		std::unique_ptr<Gops::CActorManager> m_pActorManager; // boost::scoped_ptr<Gops::CActorManager>
		INSERT_PADDING(16); // app::Util::TFreeList<app::Gops::CActor, 4>
		INSERT_PADDING(16); // app::Util::TFreeList<app::Gops::CActorPack, 4>
		std::unique_ptr<CSetAdapterMgr> m_pAdapterManager; // boost::scoped_ptr<CSetAdapterMgr>
		std::unique_ptr<Gops::CActorListener> m_pListener; // boost::scoped_ptr<Gops::CActorListener>
		alignas(16) INSERT_PADDING(144); // csl::ut::InplaceObjectMoveArrayAligned16<app::CActivationVolume, 2>
		alignas(16) INSERT_PADDING(48); // csl::ut::InplaceObjectMoveArrayAligned16<csl::math::Vector3, 2>
		float m_RangeIn;
		INSERT_PADDING(72); // PointMarkerManager
		INSERT_PADDING(24); // RespawnPointManager
		csl::ut::MoveArray<Gops::CActor*> m_Actors{ GetAllocator() };
		csl::ut::Bitset<char> m_Flags;
		void* m_Unk3;
		void* m_Unk4;
		csl::fnd::IAllocator* m_pHeapAlloc;
		INSERT_PADDING(8); // ???
		
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSendObjectMessageImpl, ASLR(0x0084CBA0), CSetObjectManager*, CSetObjectID, fnd::Message&, uint sender, bool create, bool immediate);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGetSetObjectFromUniqID, ASLR(0x0084C830), CSetObjectManager*, app::ut::RefPtr<CSetObject>&, size_t);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveListener, ASLR(0x0084BA60), CSetObjectManager*, CSetObjectListener*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpKillAllObject, ASLR(0x0084BAF0), CSetObjectManager*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStartUpLayerInfo, ASLR(0x0084C4B0), CSetObjectManager*, size_t difficulty);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadDatabase, ASLR(0x0084B910), CSetObjectManager*, size_t idx);
		inline static FUNCTION_PTR(CSetObjectListener*, __thiscall, ms_fpCreateObjectImpl, ASLR(0x0084C370), CSetObjectManager*, CSetAdapter*, CActivationManager*, uint);;

	protected:
		void SendObjectMessageImpl(CSetObjectID id, fnd::Message& rMsg, uint sender, bool create, bool immediate)
		{
			ms_fpSendObjectMessageImpl(this, id, rMsg, sender, create, immediate);
		}

		CSetObjectListener* CreateObjectImpl(CSetAdapter* pAdapter, CActivationManager* pActivationMan, uint spawnFlags)
		{
			return ms_fpCreateObjectImpl(this, pAdapter, pActivationMan, spawnFlags);
		}
		
	public:
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		void GetSetObjectFromUniqID(app::ut::RefPtr<CSetObject>& outObj, size_t id)
		{
			ms_fpGetSetObjectFromUniqID(this, outObj, id);
		}

		void SendObjectMessage(CSetObjectID id, fnd::Message& rMsg, uint sender, bool create)
		{
			SendObjectMessageImpl(id, rMsg, sender, create, false);
		}

		void SendObjectMessageImm(CSetObjectID id, fnd::Message& rMsg, uint sender, bool create)
		{
			SendObjectMessageImpl(id, rMsg, sender, create, true);
		}

		void RemoveListener(CSetObjectListener* pListener)
		{
			ms_fpRemoveListener(this, pListener);
		}

		inline void KillAllObject();
		inline CSetAdapter* FindAdapter(CSetObjectID id);
		inline SetEd::CResObject FindObjectResource(CSetObjectID id);
		
		void StartUpLayerInfo(size_t difficulty)
		{
			ms_fpStartUpLayerInfo(this, difficulty);
		}

		void LoadDatabase(size_t idx)
		{
			ms_fpLoadDatabase(this, idx);
		}

		CSetObjectListener* CreateObjectAlways(CSetAdapter* pAdapter)
		{
			return CreateObjectImpl(pAdapter, m_pActivationMan, 2);
		}

		CSetObjectListener* CreateObjectEternal(CSetAdapter* pAdapter)
		{
			return CreateObjectImpl(pAdapter, nullptr, 4);
		}

		CSetObjectListener* CreateObject(CSetAdapter* pAdapter)
		{
			uint spawnFlags = 0;
			if (m_Flags.test(2))
				spawnFlags = -1;
			
			return CreateObjectImpl(pAdapter, m_pActivationMan, spawnFlags);
		}
		
		CSetObjectListener* CreateObjectExtrinsic(CSetAdapter* pAdapter)
		{
			return CreateObjectImpl(pAdapter, nullptr, 16);
		}

		CSetObjectListener* CreateObjectEditing(CSetAdapter* pAdapter)
		{
			return CreateObjectImpl(pAdapter, nullptr, -1);
		}
		
		CSetObjectListener* CreateObjectBySetObjectID(CSetObjectID id);

		void LoadObjectResources()
		{
			auto* pResContainer = m_pOwnerDocument->GetService<CObjInfoContainer>();
			if (pResContainer)
				pResContainer->LoadRequestAll();
		}
	};
}

#include "SetObjectManager.inl"