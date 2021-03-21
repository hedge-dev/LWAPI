#pragma once

namespace app::animation
{
	class ComplexImpl : public fnd::ReferencedObject, public AnimationNode
	{
	protected:
		void* m_pUnk1{};
		csl::ut::InplaceMoveArray<ut::RefPtr<ComplexBlender>, 3> m_Blenders{ GetAllocator() };
		csl::ut::StringMap<ComplexBlender*> m_BlenderMap{ GetAllocator() };

		virtual void Setup() = 0;
		virtual void Cleanup() = 0;
		virtual AnimationClip* GetCurrentClip() = 0;

	public:
		const csl::ut::StringMap<ComplexBlender*>& GetBlenders() const
		{
			return m_BlenderMap;
		}
	};
}