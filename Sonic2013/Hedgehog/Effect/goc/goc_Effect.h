#pragma once

namespace app::effect
{
	enum EffectGroup {};
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
		int	m_Unk4{};
		int	m_Unk5{};
		int	m_Unk6{};
		fnd::GOCVisual* m_pVisual{};
		const char* m_pBoneName{};
		int	m_Unk9{};
		int	m_Unk10{};
	};

	struct EffectFollowInfo
	{

	};

	class GOCEffect : public fnd::GOComponent
	{
		int m_Unk3{};
		int m_Unk4{};
		int m_Unk5{};
		float m_Unk6{};
		csl::ut::Enum<GlobalScaleType, char> m_GlobalScale{};
		csl::ut::Enum<effect::EffectGroup, char> m_Group{};
		csl::ut::ObjectMoveArray<EffectFollowInfo> m_FollowInfos{ m_pAllocator };
		INSERT_PADDING(24); // csl::ut::Queue<NodeEffectRequest>

	private:
		inline static FUNCTION_PTR(void, __cdecl, ms_fpSimpleSetup, ASLR(0x004BD9D0), GameObject* pObject, size_t a2, bool a3);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEffect, ASLR(0x004BD5F0), GOCEffect* pThis, const char* pName);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEffectEx, ASLR(0x004BDA20), GOCEffect* pThis, const EffectCreateInfo& rInfo);
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

		static void SimpleSetup(GameObject* pObject, size_t a2, bool a3)
		{
			ms_fpSimpleSetup(pObject, a2, a3);
		}
	};
}