#pragma once
#define DELTA_TIME (1.0f / 60.0f)

namespace app::animation
{
	class SkeletonBlender;
}

namespace app::game
{
	enum class PlayPolicy
	{
		Once,
		Loop
	};
	
	class AnimationControl;
	class AnimationControlBase
	{
	public:
		struct Description
		{
			
		};

		virtual ~AnimationControlBase() = default;
		virtual void Setup(Description& description, csl::fnd::IAllocator* pAllocator) = 0;
		virtual void Cleanup() = 0;
		virtual float GetFrame() const = 0;
		virtual void SetFrame(float frame) = 0;
		virtual float GetEndFrame() const = 0;
		virtual float GetSpeed() const = 0;
		virtual void SetSpeed(float speed) = 0;
		virtual bool Compare(const char* pOther) const = 0;
		virtual const char* GetName() const = 0;
		virtual bool IsValid() const = 0;
		virtual void Attach(animation::SkeletonBlenderBase* pBlender) = 0;
		virtual void Detach(animation::SkeletonBlenderBase* pBlender) = 0;
	};

	class AnimationControlHH : public AnimationControlBase
	{
	protected:
		animation::SkeletonControlBase* m_pSkeletonController{};
		csl::ut::FixedString<32> m_Name{};
		INSERT_PADDING(8){};
	};
	
	class GOCAnimationSimple : public GOCAnimationSingle
	{
	public:
		struct Description
		{
			size_t m_AnimCount{};
		};
		
	protected:
		fnd::GOCVisualModel* m_pVisual{};
		csl::ut::ObjectMoveArray<AnimationControlHH> m_Controls{ GetAllocator() };
		AnimationControlBase* m_pCurrentAnimation{};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpCleaup, ASLR(0x004B3CC0), GOCAnimationSimple*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004B3C80), GOCAnimationSimple*, const Description&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAdd, ASLR(0x004B3E50), GOCAnimationSimple*, const char*, hh::gfx::res::ResAnimSkeleton*, PlayPolicy);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetAnimation, ASLR(0x004B3A80), GOCAnimationSimple*, const char*);
		
		void Cleanup()
		{
			ms_fpCleaup(this);
		}

		AnimationControlBase* FindAnimation(const char* pName) const
		{
			for (auto& control : m_Controls)
			{
				if (control.Compare(pName))
					return &control;
			}
			
			return nullptr;
		}
	public:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7534));
		
		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& desc)
		{
			ms_fpSetup(this, desc);
		}
		
		void Add(const char* pName, hh::gfx::res::ResAnimSkeleton* pAnimation, PlayPolicy policy)
		{
			ms_fpAdd(this, pName, pAnimation, policy);
		}

		void SetAnimation(const char* pName)
		{
			if (!m_pVisual)
				return;

			auto* pAnim = FindAnimation(pName);

			if (!pAnim)
				return;

			if (m_pCurrentAnimation)
				m_pCurrentAnimation->Detach(m_pSkeletalBlender);

			m_pCurrentAnimation = pAnim;
			pAnim->Attach(m_pSkeletalBlender);
			pAnim->SetSpeed(1);
			pAnim->SetFrame(0);
		}

		void SetSpeed(float speed) const
		{
			if (m_pCurrentAnimation)
				m_pCurrentAnimation->SetSpeed(speed);
		}

		void SetFrame(float frame) const
		{
			if (m_pCurrentAnimation)
				m_pCurrentAnimation->SetFrame(frame);
		}

		float GetSpeed() const
		{
			if (m_pCurrentAnimation)
				return m_pCurrentAnimation->GetSpeed();

			return 0;
		}

		float GetFrame() const
		{
			if (m_pCurrentAnimation)
				return m_pCurrentAnimation->GetFrame();
			
			return 0;
		}

		float GetEndFrame() const
		{
			if (m_pCurrentAnimation)
				return m_pCurrentAnimation->GetEndFrame();

			return 0;
		}

		const char* GetAnimation() const
		{
			if (m_pCurrentAnimation)
				return m_pCurrentAnimation->GetName();
			
			return nullptr;
		}

		bool IsFinished() const
		{
			if (!m_pCurrentAnimation)
				return false;

			return m_pCurrentAnimation->GetFrame() >= m_pCurrentAnimation->GetEndFrame();
		}
	};
}