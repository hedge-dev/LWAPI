#pragma once
#define DELTA_TIME (1.0f / 60.0f)

namespace app::animation
{
	class SkeletonBlender;
}

namespace app::game
{
	class AnimationControl;

	enum class PlayPolicy
	{
		Once,
		Loop
	};
	
	class AnimationControlBase
	{
	public:
		struct Description
		{
			
		};

		virtual ~AnimationControlBase() = default;
		virtual void Setup(Description& in_rDescription, csl::fnd::IAllocator* in_pAllocator) = 0;
		virtual void Cleanup() = 0;
		virtual float GetFrame() const = 0;
		virtual void SetFrame(float in_frame) = 0;
		virtual float GetEndFrame() const = 0;
		virtual float GetSpeed() const = 0;
		virtual void SetSpeed(float in_speed) = 0;
		virtual bool Compare(const char* in_pOther) const = 0;
		virtual const char* GetName() const = 0;
		virtual bool IsValid() const = 0;
		virtual void Attach(animation::SkeletonBlender* in_pBlender) = 0;
		virtual void Detach(animation::SkeletonBlender* in_pBlender) = 0;
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
			size_t AnimCount{};
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCleaup, ASLR(0x004B3CC0), GOCAnimationSimple*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004B3C80), GOCAnimationSimple*, const Description&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAdd, ASLR(0x004B3E50), GOCAnimationSimple*, const char*, hh::gfx::res::ResAnimSkeleton, PlayPolicy);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetAnimation, ASLR(0x004B3A80), GOCAnimationSimple*, const char*);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7534));

	protected:
		csl::ut::ObjectMoveArray<AnimationControlHH> m_Controls{ GetAllocator() };
		AnimationControlBase* m_pCurrentAnimation{};
		
		void Cleanup()
		{
			ms_fpCleaup(this);
		}

		AnimationControlBase* FindAnimation(const char* in_pName) const
		{
			for (auto& control : m_Controls)
			{
				if (control.Compare(in_pName))
					return &control;
			}
			
			return nullptr;
		}

	public:
		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& in_rDesc)
		{
			ms_fpSetup(this, in_rDesc);
		}
		
		void Add(const char* in_pName, hh::gfx::res::ResAnimSkeleton in_animation, PlayPolicy in_policy)
		{
			ms_fpAdd(this, in_pName, in_animation, in_policy);
		}

		void SetAnimation(const char* in_pName)
		{
			if (!pModel)
				return;

			auto* pAnim = FindAnimation(in_pName);

			if (!pAnim)
				return;

			if (m_pCurrentAnimation)
				m_pCurrentAnimation->Detach(pBlender);

			m_pCurrentAnimation = pAnim;
			pAnim->Attach(pBlender);
			pAnim->SetSpeed(1);
			pAnim->SetFrame(0);
		}

		void SetSpeed(float in_speed) const
		{
			if (m_pCurrentAnimation)
				m_pCurrentAnimation->SetSpeed(in_speed);
		}

		void SetFrame(float in_frame) const
		{
			if (m_pCurrentAnimation)
				m_pCurrentAnimation->SetFrame(in_frame);
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

		bool IsCurrentAnimation(const char* in_pAnimationName) const
		{
			if (!m_pCurrentAnimation)
				return false;

			return m_pCurrentAnimation->Compare(in_pAnimationName);
		}
	};
}