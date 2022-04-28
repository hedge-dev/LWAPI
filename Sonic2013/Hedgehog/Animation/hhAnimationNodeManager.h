#pragma once

namespace app::animation
{
	class CharactorAnimation;
	class AnimationClip;
	class AnimationSimple;
	class AnimationComplex;
	
	class AnimationNodeManager
	{
		struct ExtendToken;
	public:
		csl::ut::StringMap<AnimationClip*> m_Animations;
		AnimSkeletonBlender m_Blender{ nullptr };
		csl::ut::ObjectMoveArray<AnimationSimple> m_SimpleAnimations;
		csl::ut::ObjectMoveArray<AnimationComplex> m_ComplexAnimations;
		CharactorAnimation* m_pOwner{};
		csl::fnd::IAllocator* m_pAllocator{};
		csl::ut::ObjectMoveArray<ut::RefPtr<ExternalAnimtion>> m_ExternalAnimations;
		
		AnimationNodeManager(csl::fnd::IAllocator& rAlloc) : m_Animations(&rAlloc), m_SimpleAnimations(&rAlloc),
			m_ComplexAnimations(&rAlloc), m_ExternalAnimations(&rAlloc)
		{
			m_pAllocator = &rAlloc;
		}

		void AttachAnimSkeletonBlender(AnimSkeletonBlender& in_blender)
		{
			m_Blender = in_blender;
		}

		void Setup(CharactorAnimation* in_pOwner, size_t in_simpleCount, size_t in_complexCount)
		{
			m_pOwner = in_pOwner;
			m_SimpleAnimations.resize(in_simpleCount);
			for (auto& anim : m_SimpleAnimations)
			{
				anim.m_pOwner = m_pOwner;
				anim.m_pManager = this;
				anim.ProcEvent(AnimationNode::eEvent_AttachExternal);
			}

			m_ComplexAnimations.resize(in_complexCount);
			for (auto& anim : m_ComplexAnimations)
			{
				anim.m_pOwner = m_pOwner;
				anim.m_pManager = this;
				anim.ProcEvent(AnimationNode::eEvent_AttachExternal);
			}
		}

		ExtendToken SetupExtend(size_t in_simpleCount, size_t in_complexCount)
		{
			ExtendToken token{ m_SimpleAnimations.size(), m_ComplexAnimations.size() };
			m_Animations.clear();
			m_SimpleAnimations.resize(token.m_SimpleStartIdx + in_simpleCount);
			m_ComplexAnimations.resize(token.m_ComplexStartIdx + in_complexCount);

			for (size_t i = token.m_SimpleStartIdx; i < m_SimpleAnimations.size(); i++)
			{
				auto& anim = m_SimpleAnimations[i];
				anim.m_pOwner = m_pOwner;
				anim.m_pManager = this;
				anim.ProcEvent(AnimationNode::eEvent_AttachExternal);
			}

			for (size_t i = token.m_ComplexStartIdx; i < m_ComplexAnimations.size(); i++)
			{
				auto& anim = m_ComplexAnimations[i];
				anim.m_pOwner = m_pOwner;
				anim.m_pManager = this;
				anim.ProcEvent(AnimationNode::eEvent_AttachExternal);
			}

			for (size_t i = 0; i < token.m_SimpleStartIdx; i++)
				m_Animations.insert(m_SimpleAnimations[i].GetAnimationDef()->m_pName, &m_SimpleAnimations[i]);

			for (size_t i = 0; i < token.m_ComplexStartIdx; i++)
				m_Animations.insert(m_ComplexAnimations[i].GetAnimationDef()->m_pName, &m_ComplexAnimations[i]);

			return token;
		}

		void ResisterAnimations(const AnimationResContainer::ResData& in_data)
		{
			auto& anims = in_data.m_pFile->m_pAnimations;
			for (size_t i = 0; i < anims->m_SimpleAnimations.m_Count; ++i)
			{
				m_SimpleAnimations[i].Setup(*m_pAllocator, anims->m_SimpleAnimations.m_pAnimations[i], in_data.m_SimpleAnimations[i]);
				m_Animations.insert(anims->m_SimpleAnimations.m_pAnimations[i].m_pName, &m_SimpleAnimations[i]);
			}

			size_t cmplxOff{};
			for (size_t i = 0; i < anims->m_ComplexAnimations.m_Count; ++i)
			{
				m_ComplexAnimations[i].Setup(*m_pAllocator, anims->m_ComplexAnimations.m_pAnimations[i], in_data.m_ComplexAnimations, cmplxOff);
				m_Animations.insert(anims->m_ComplexAnimations.m_pAnimations[i].m_pName, &m_ComplexAnimations[i]);

				cmplxOff += anims->m_ComplexAnimations.m_pAnimations[i].m_Animations.m_Count;
			}
		}

		void ResisterAnimationsExtend(const AnimationResContainer::ResData& in_data, const ExtendToken& token)
		{
			auto& anims = in_data.m_pFile->m_pAnimations;

			size_t idx{};
			for (size_t i = token.m_SimpleStartIdx; i < m_SimpleAnimations.size(); ++i)
			{
				m_SimpleAnimations[i].Setup(*m_pAllocator, anims->m_SimpleAnimations.m_pAnimations[idx], in_data.m_SimpleAnimations[idx]);
				m_Animations.insert(anims->m_SimpleAnimations.m_pAnimations[idx].m_pName, &m_SimpleAnimations[i]);
				++idx;
			}

			idx = 0;
			size_t cmplxOff{};
			for (size_t i = token.m_ComplexStartIdx; i < m_ComplexAnimations.size(); ++i)
			{
				m_ComplexAnimations[i].Setup(*m_pAllocator, anims->m_ComplexAnimations.m_pAnimations[idx], in_data.m_ComplexAnimations, cmplxOff);
				m_Animations.insert(anims->m_ComplexAnimations.m_pAnimations[idx].m_pName, &m_ComplexAnimations[i]);

				cmplxOff += anims->m_ComplexAnimations.m_pAnimations[idx].m_Animations.m_Count;
			}
		}

		void Cleanup()
		{
			for (auto& anim : m_SimpleAnimations)
			{
				anim.Cleanup();
				anim.ProcEvent(AnimationNode::eEvent_FinishCleanup);
			}

			for (auto& anim : m_ComplexAnimations)
			{
				anim.Cleanup();
				anim.ProcEvent(AnimationNode::eEvent_FinishCleanup);
			}

			if (!m_SimpleAnimations.empty())
				m_SimpleAnimations.clear();

			if (!m_ComplexAnimations.empty())
				m_ComplexAnimations.clear();
		}

		void SetExternal(ExternalAnimtion* pAnim)
		{
			ut::RefPtr rpAnim = pAnim;
			m_ExternalAnimations.push_back(rpAnim);

			auto* pClip = pAnim->GetSimpleAnimation();
			pClip->m_pManager = this;
			pClip->m_pOwner = m_pOwner;
			pClip->ProcEvent(AnimationNode::eEvent_AttachExternal);
		}
		
		AnimationClip* GetAnimationClip(const char* pName) const
		{
			const auto result = m_Animations.find(pName);
			if (result == m_Animations.end())
				return nullptr;

			return result;
		}

		struct ExtendToken
		{
			size_t m_SimpleStartIdx{};
			size_t m_ComplexStartIdx{};
		};
	};
}