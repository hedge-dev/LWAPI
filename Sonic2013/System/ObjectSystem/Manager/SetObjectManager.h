#pragma once

namespace app
{
	class CActivationManager;

	struct SLayerInfo
	{
		csl::ut::Bitset<uint> Flags;
		void* Unk1;
		csl::ut::FixedString<64> Name;
	};

	class CSetObjectManager : public fnd::GameService
	{
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEF2E8));

	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSendObjectMessageImpl, ASLR(0x0084CBA0), CSetObjectManager*, CSetObjectID, fnd::Message&, uint sender, bool create, bool immediate);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGetSetObjectFromUniqID, ASLR(0x0084C830), CSetObjectManager*, app::ut::RefPtr<CSetObject>&, size_t);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveListener, ASLR(0x0084BA60), CSetObjectManager*, CSetObjectListener*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpKillAllObject, ASLR(0x0084BAF0), CSetObjectManager*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStartUpLayerInfo, ASLR(0x0084C4B0), CSetObjectManager*, size_t);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadDatabase, ASLR(0x0084B910), CSetObjectManager*, size_t);
		inline static FUNCTION_PTR(CSetObjectListener*, __thiscall, ms_fpCreateObjectImpl, ASLR(0x0084C370), CSetObjectManager*, CSetAdapter*, CActivationManager*, uint);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRangeInSetObject, ASLR(0x0084D620), CSetObjectManager*, const csl::math::Vector3&);

	public:
		GameDocument* pDocument;
		boost::shared_ptr<CSetObjectFactory> spObjectFactory;
		csl::ut::LinkList<CSetObjectListener> Objects;
		SLayerInfo Layers[9];
		size_t CurrentLayerIdx;
		CLevelInfo* pLevelInfo;
		CActivationManager* pActivationMan;
		app::ut::RefPtr<SetEd::CResource> rpRes;
		std::unique_ptr<Gops::CActorManager> pActorManager; // boost::scoped_ptr<Gops::CActorManager>
		INSERT_PADDING(16); // app::Util::TFreeList<app::Gops::CActor, 4>
		INSERT_PADDING(16); // app::Util::TFreeList<app::Gops::CActorPack, 4>
		std::unique_ptr<CSetAdapterMgr> pAdapterManager; // boost::scoped_ptr<CSetAdapterMgr>
		std::unique_ptr<Gops::CActorListener> pListener; // boost::scoped_ptr<Gops::CActorListener>
		csl::ut::InplaceObjectMoveArrayAligned16<app::CActivationVolume, 2> Volumes;
		csl::ut::InplaceObjectMoveArrayAligned16<csl::math::Vector3, 2> BasePoints;
		float RangeIn;
		INSERT_PADDING(72); // PointMarkerManager
		INSERT_PADDING(24); // RespawnPointManager
		csl::ut::MoveArray<Gops::CActor*> Actors{ GetAllocator() };
		csl::ut::Bitset<char> Flags;
		void* Unk3;
		void* Unk4;
		csl::fnd::IAllocator* pHeapAlloc;
		INSERT_PADDING(8); // ???

	protected:
		bool SendObjectMessageImpl(CSetObjectID in_id, fnd::Message& in_rMessage, uint in_sender, bool in_create, bool in_immediate)
		{
			return ms_fpSendObjectMessageImpl(this, in_id, in_rMessage, in_sender, in_create, in_immediate);
		}

		CSetObjectListener* CreateObjectImpl(CSetAdapter* in_pAdapter, CActivationManager* in_pActivationMan, uint in_spawnFlags)
		{
			return ms_fpCreateObjectImpl(this, in_pAdapter, in_pActivationMan, in_spawnFlags);
		}
		
	public:
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		size_t GetLayerIDFromUID(CSetObjectID in_id) const
		{
			return in_id.Value / 4000;
		}

		SetEd::CResObject GetResObjectByID(CSetObjectID in_id) const
		{
			auto* pProject = rpRes->GetObjectProject(GetLayerIDFromUID(in_id));
			if (!pProject)
				return { nullptr };
			
			return pProject->GetObjectByID(id);
		}

		void GetSetObjectFromUniqID(app::ut::RefPtr<CSetObject>& in_rOutObj, size_t in_id)
		{
			ms_fpGetSetObjectFromUniqID(this, in_rOutObj, in_id);
		}

		void SendObjectMessage(CSetObjectID in_id, fnd::Message& in_rMessage, uint in_sender, bool in_create)
		{
			SendObjectMessageImpl(in_id, in_rMessage, in_sender, in_create, false);
		}

		bool SendObjectMessageImm(CSetObjectID in_id, fnd::Message& in_rMessage, uint in_sender, bool in_create)
		{
			return SendObjectMessageImpl(in_id, in_rMessage, in_sender, in_create, true);
		}

		void RemoveListener(CSetObjectListener* in_pListener)
		{
			ms_fpRemoveListener(this, in_pListener);
		}

		inline void KillAllObject();
		inline CSetAdapter* FindAdapter(CSetObjectID in_id);
		inline SetEd::CResObject FindObjectResource(CSetObjectID in_id);
		
		void StartUpLayerInfo(size_t in_difficulty)
		{
			ms_fpStartUpLayerInfo(this, in_difficulty);
		}

		void LoadDatabase(size_t in_idx)
		{
			ms_fpLoadDatabase(this, in_idx);
		}

		void RangeInSetObject(const csl::math::Vector3& in_rPos)
		{
			ms_fpRangeInSetObject(this, in_rPos);
		}

		void SetBasePos(size_t in_unit, const csl::math::Vector3& in_rPos)
		{
			if (BasePoints.size() <= in_unit)
			{
				BasePoints.resize(unit + 1);
				size_t oldSize = Volumes.size();
				Volumes.resize(unit + 1);
				if (oldSize)
				{
					for (size_t i = oldSize; i < Volumes.size(); i++)
					{
						pActivationMan->AddVolume(&Volumes[i]);
					}
				}
			}
			
			BasePoints[unit] = in_rPos;
			Volumes[unit].SetVolume({ in_rPos, RangeIn + 200 });
		}
		
		CSetObjectListener* CreateObjectAlways(CSetAdapter* in_pAdapter)
		{
			return CreateObjectImpl(in_pAdapter, pActivationMan, 2);
		}

		CSetObjectListener* CreateObjectEternal(CSetAdapter* in_pAdapter)
		{
			return CreateObjectImpl(in_pAdapter, nullptr, 4);
		}

		CSetObjectListener* CreateObject(CSetAdapter* in_pAdapter)
		{
			uint spawnFlags = 0;
			if (Flags.test(2))
				spawnFlags = -1;
			
			return CreateObjectImpl(pAdapter, pActivationMan, spawnFlags);
		}
		
		CSetObjectListener* CreateObjectExtrinsic(CSetAdapter* in_pAdapter)
		{
			return CreateObjectImpl(in_pAdapter, nullptr, 16);
		}

		CSetObjectListener* CreateObjectEditing(CSetAdapter* in_pAdapter)
		{
			return CreateObjectImpl(in_pAdapter, nullptr, -1);
		}
		
		CSetObjectListener* CreateObjectBySetObjectID(CSetObjectID in_id);

		void LoadObjectResources()
		{
			auto* pResContainer = pOwnerDocument->GetService<CObjInfoContainer>();
			if (pResContainer)
				pResContainer->LoadRequestAll();
		}
	};
}

#include "SetObjectManager.inl"