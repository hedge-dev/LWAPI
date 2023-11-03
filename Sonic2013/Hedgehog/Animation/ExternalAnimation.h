#pragma once

namespace app::animation
{
	struct CreateSimpleDefInfo
	{
		const char* pName;
		EPlayMode PlayMode{ EPlayMode::ePlayMode_Stop };
		ResCharAnim AnimResource{ nullptr };
	};

	class ExternalAnimtion : public fnd::ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateSimpleDefResource, ASLR(0x00415430), ExternalAnimtion*, const CreateSimpleDefInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateDefaultInterpolate, ASLR(0x004156A0), ExternalAnimtion*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateSimpleClip, ASLR(0x00415610), ExternalAnimtion*);

	protected:
		csl::ut::MoveArray<void*> m_Buffers{ GetAllocator() };
		SimpleDef* m_pAnimDef;
		AnimationSimple* m_pClip;
		ResCharAnim m_Animation{ nullptr };
		
	public:
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
		
		void CreateSimpleDefResource(const CreateSimpleDefInfo& in_rInfo)
		{
			ms_fpCreateSimpleDefResource(this, in_rInfo);
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

	inline static ExternalAnimtion* CreateExternalAnimation(const CreateSimpleDefInfo& in_rInfo, csl::fnd::IAllocator& in_rAlloc)
	{
		ExternalAnimtion* pAnim = new(in_rAlloc) ExternalAnimtion();
		if (!pAnim)
			return pAnim;
		
		pAnim->CreateSimpleDefResource(in_rInfo);
		pAnim->CreateDefaultInterpolate();
		pAnim->CreateSimpleClip();
		
		return pAnim;
	}
}