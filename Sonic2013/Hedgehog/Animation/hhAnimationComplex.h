#pragma once

namespace app::animation
{
	class AnimationSimple;
	class AnimationComplex : public AnimationClip
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00F61148))
		
	public:
		const ComplexDef* m_pDef{};
		ut::RefPtr<ComplexImpl> m_pImpl{};

	protected:
		csl::ut::ObjectMoveArray<AnimationSimple> m_Animations{ nullptr };
		csl::ut::LinkList<AnimationClip> m_Clips{ 12 };
		float m_Weight{ 1 };
		
		AnimationComplex()
		{
			
		}
	};

	inline static ComplexBlender* GetBlender(const char* pName, const AnimationClip& rClip)
	{
		auto* pComplex = csl::ut::DynamicCast<const AnimationComplex>(&rClip);
		if (!pComplex)
			return nullptr;

		if (!pComplex->m_pDef->m_pData->m_BlenderInfo.IsValid())
			return nullptr;

		return pComplex->m_pImpl->GetBlenders().find(pName);
	}
}