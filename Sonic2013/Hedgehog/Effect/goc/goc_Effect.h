#pragma once

namespace app::effect
{	
	enum EffectGroup {};
}

namespace app::Effect
{
	template <typename T = hh::eff::CEffectInstance>
	class CEffectHandle
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStop, ASLR(0x0047EEA0), CEffectHandle<hh::eff::CEffectInstance>*, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetVisible, ASLR(0x0047EF60), CEffectHandle<>*, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetGlobalScaling, ASLR(0x0047EEC0), CEffectHandle<>*, float);

	public:
		hh::eff::CInstanceHandle<T> InstanceHandle{};

		virtual ~CEffectHandle() = default;

		bool IsValid() const
		{
			if (!InstanceHandle.m_pEntry)
				return false;

			return InstanceHandle.m_pEntry->m_pHandle && (InstanceHandle.m_EffectHandle == InstanceHandle.m_pEntry->m_Effect);
		}

		T* GetInstance() const
		{
			if (!IsValid())
				return { nullptr };

			return static_cast<T*>(InstanceHandle.m_pEntry->m_pHandle);
		}

		void Stop(bool in_unk)
		{
			ms_fpStop(this, in_unk);
		}

		void SetVisible(bool in_isVisible)
		{
			ms_fpSetVisible(this, in_isVisible);
		}

		void SetGlobalScaling(float in_scale)
		{
			ms_fpSetGlobalScaling(this, in_scale);
		}
	};

	class EffectDataSetupHelper
	{
	public:
		INSERT_PADDING(52);
		csl::ut::MoveArray<const char*> EffectMaterials{};

	public:
		void SetupColorScaleMaterialList(const char** in_ppMaterialList, int in_count)
		{
			EffectMaterials.reserve(in_count);
			
			for (size_t i = 0; i < in_count; i++)
			{
				EffectMaterials.push_back_unchecked(*in_ppMaterialList);

				in_ppMaterialList++;
			}

			std::sort(EffectMaterials.begin(), EffectMaterials.end(), CompareName);
		}

		static bool CompareName(const char* in_pLeft, const char* in_pRight)
		{
			return strcmp(in_pLeft, in_pRight) < 0;
		}
	};

	class CEffectManager : public fnd::GameService
	{
	public:
		class Impl
		{
		public:
			INSERT_PADDING(24) {};
			Effect::EffectDataSetupHelper* pSetupHelper{};
			INSERT_PADDING(4) {};
		};

		class MyRenderable
		{
		public:
			INSERT_PADDING(120) {};
			int Unk1{};
			INSERT_PADDING(8) {};
		};

	private:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FD40CC));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEffect, ASLR(0x0047F5A0), CEffectManager*, CEffectHandle<hh::eff::CEffectInstance>*, const char*, const csl::math::Matrix34&, int);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetStageName, ASLR(0x00480F20), CEffectManager*, const csl::ut::FixedString<16>&);
		
	public:
		Impl* pImpl{};
		int Unk2{};
		MyRenderable* pRenderables[2]{};
		
		CEffectManager() : fnd::GameService(0)
		{
			
		}

		void CreateEffect(CEffectHandle<hh::eff::CEffectInstance>* out_pHandle, const char* in_pEffectName, const csl::math::Matrix34& in_rMtx, int in_Unk1)
		{
			ms_fpCreateEffect(this, out_pHandle, in_pEffectName, in_rMtx, in_Unk1);
		}

		void SetStageName(const csl::ut::FixedString<16>& in_rStageName)
		{
			ms_fpSetStageName(this, in_rStageName);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}

namespace app::game
{
	enum GlobalScaleType {};

	struct EffectCreateInfo
	{
		const char* m_pName{};
		float m_Unk1{};
		int m_Unk2{};
		csl::math::Vector3 m_Position{};
		csl::math::Quaternion m_Rotation{ 0, 0, 0, 1 };
		bool m_Unk3{};
		int m_Unk4{};
		int m_Unk5{};
		int m_Unk6{};
		fnd::GOCVisual* m_pVisual{};
		const char* m_pBoneName{};
		int m_Unk9{};
		int m_Unk10{};
	};

	struct EffectFollowInfo
	{

	};

	class GOCEffect : public fnd::GOComponent
	{
	public:
		int m_Unk3{};
		fnd::HFrame* pFrame{};
		int m_Unk5{};
		float GlobalScaling{};
		csl::ut::Enum<GlobalScaleType, char> m_GlobalScale{};
		csl::ut::Enum<effect::EffectGroup, char> m_Group{};
		csl::ut::ObjectMoveArray<EffectFollowInfo> m_FollowInfos{ m_pAllocator };
		INSERT_PADDING(24); // csl::ut::Queue<NodeEffectRequest>

	private:
		inline static FUNCTION_PTR(void, __cdecl, ms_fpSimpleSetup, ASLR(0x004BD9D0), GameObject*, size_t a2, bool a3);
		inline static FUNCTION_PTR(void, __cdecl, ms_fpSimpleSetup2, ASLR(0x004BD980), GameObject*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEffect, ASLR(0x004BD5F0), GOCEffect*, const char* pName);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEffectEx, ASLR(0x004BDA20), GOCEffect*, const EffectCreateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEffectLoop, ASLR(0x004BDFD0), GOCEffect*, Effect::CEffectHandle<hh::eff::CEffectInstance>*, const char*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEffectLoopEx, ASLR(0x004BDDC0), GOCEffect*, Effect::CEffectHandle<hh::eff::CEffectInstance>*, const EffectCreateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEffectWorld, ASLR(0x004BD330), GOCEffect*, const char*, const csl::math::Matrix34&, float);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7630));

	public:
		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void CreateEffect(const char* pName)
		{
			ms_fpCreateEffect(this, pName);
		}

		void CreateEffectEx(const EffectCreateInfo& rInfo)
		{
			ms_fpCreateEffectEx(this, rInfo);
		}

		void CreateEffectLoop(Effect::CEffectHandle<hh::eff::CEffectInstance>* out_pHandle, const char* in_pName)
		{
			ms_fpCreateEffectLoop(this, out_pHandle, in_pName);
		}

		void CreateEffectLoopEx(Effect::CEffectHandle<hh::eff::CEffectInstance>* out_pHandle, const EffectCreateInfo& in_rInfo)
		{
			ms_fpCreateEffectLoopEx(this, out_pHandle, in_rInfo);
		}

		void CreateEffectWorld(const char* in_pName, const csl::math::Matrix34& in_rTransformMtx, float in_unk)
		{
			ms_fpCreateEffectWorld(this, in_pName, in_rTransformMtx, in_unk);
		}

		static void SimpleSetup(GameObject* in_pObject)
		{
			ms_fpSimpleSetup2(in_pObject);
		}

		static void SimpleSetup(GameObject* pObject, size_t a2, bool a3)
		{
			ms_fpSimpleSetup(pObject, a2, a3);
		}
	};
}