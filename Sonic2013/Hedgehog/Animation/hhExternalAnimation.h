#pragma once

namespace app::animation
{
	struct CreateSimpleDefInfo
	{
		const char* m_pName;
		EPlayMode m_PlayMode{ EPlayMode::ePlayMode_Stop };
		ResCharAnim m_AnimResource{ nullptr };
	};

	class ExternalAnimtion : public fnd::ReferencedObject
	{
	protected:
		csl::ut::MoveArray<void*> m_Buffers{ GetAllocator() };
		SimpleDef* m_pAnimDef;
		AnimationSimple* m_pClip;
		ResCharAnim m_Animation{ nullptr };

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateSimpleDefResource, ASLR(0x00415430), ExternalAnimtion* pThis, const CreateSimpleDefInfo& rInfo);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateDefaultInterpolate, ASLR(0x004156A0), ExternalAnimtion* pThis);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateSimpleClip, ASLR(0x00415610), ExternalAnimtion* pThis);
		
		ExternalAnimtion()
		{
			
		}

		const SimpleDef* GetAnimationDef() const
		{
			return m_pAnimDef;
		}
		
		AnimationSimple* GetSimpleAnimation() const
		{
			return m_pClip;
		}
		
		void CreateSimpleDefResource(const CreateSimpleDefInfo& rInfo)
		{
			ms_fpCreateSimpleDefResource(this, rInfo);
		}

		void CreateDefaultInterpolate()
		{
			ms_fpCreateDefaultInterpolate(this);
		}

		void CreateSimpleClip()
		{
			ms_fpCreateSimpleClip(this);
		}
		
		~ExternalAnimtion()
		{
			if (m_pClip)
				m_pClip->~AnimationSimple();

			auto* pAlloc = m_Buffers.get_allocator();
			if (!pAlloc)
				return;

			for (auto& buffer : m_Buffers)
			{
				pAlloc->Free(buffer);
			}
		}
	};

	inline static ExternalAnimtion* CreateExternalAnimation(const CreateSimpleDefInfo& rInfo, csl::fnd::IAllocator& rAlloc)
	{
		ExternalAnimtion* pAnim = new(rAlloc) ExternalAnimtion();
		if (!pAnim)
			return pAnim;
		
		pAnim->CreateSimpleDefResource(rInfo);
		pAnim->CreateDefaultInterpolate();
		pAnim->CreateSimpleClip();
		
		return pAnim;
	}
}