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
		csl::ut::StringMap<AnimationClip*> Animations;
		AnimSkeletonBlender Blender{ nullptr };
		csl::ut::ObjectMoveArray<AnimationSimple> SimpleAnimations;
		csl::ut::ObjectMoveArray<AnimationComplex> ComplexAnimations;
		CharactorAnimation* pOwner{};
		csl::fnd::IAllocator* pAllocator{};
		csl::ut::ObjectMoveArray<ut::RefPtr<ExternalAnimtion>> ExternalAnimations;
		
		AnimationNodeManager(csl::fnd::IAllocator& in_rAlloc) : m_Animations(&in_rAlloc), m_SimpleAnimations(&in_rAlloc),
			m_ComplexAnimations(&in_rAlloc), m_ExternalAnimations(&in_rAlloc)
		{
			pAllocator = &in_rAlloc;
		}

		void AttachAnimSkeletonBlender(AnimSkeletonBlender& in_rBlender)
		{
			Blender = in_rBlender;
		}

		void Setup(CharactorAnimation* in_pOwner, size_t in_simpleCount, size_t in_complexCount)
		{
			pOwner = in_pOwner;
			SimpleAnimations.resize(in_simpleCount);
			for (auto& anim : SimpleAnimations)
			{
				anim.pOwner = pOwner;
				anim.pManager = this;
				anim.ProcEvent(AnimationNode::eEvent_AttachExternal);
			}

			m_ComplexAnimations.resize(in_complexCount);
			for (auto& anim : ComplexAnimations)
			{
				anim.pOwner = pOwner;
				anim.pManager = this;
				anim.ProcEvent(AnimationNode::eEvent_AttachExternal);
			}
		}

		ExtendToken SetupExtend(size_t in_simpleCount, size_t in_complexCount)
		{
			ExtendToken token{ SimpleAnimations.size(), ComplexAnimations.size() };
			Animations.clear();
			SimpleAnimations.resize(token.SimpleStartIdx + in_simpleCount);
			ComplexAnimations.resize(token.ComplexStartIdx + in_complexCount);

			for (size_t i = token.SimpleStartIdx; i < SimpleAnimations.size(); i++)
			{
				auto& anim = SimpleAnimations[i];
				anim.pOwner = pOwner;
				anim.pManager = this;
				anim.ProcEvent(AnimationNode::eEvent_AttachExternal);
			}

			for (size_t i = token.ComplexStartIdx; i < ComplexAnimations.size(); i++)
			{
				auto& anim = ComplexAnimations[i];
				anim.pOwner = pOwner;
				anim.pManager = this;
				anim.ProcEvent(AnimationNode::eEvent_AttachExternal);
			}

			for (size_t i = 0; i < token.SimpleStartIdx; i++)
				Animations.insert(SimpleAnimations[i].GetAnimationDef()->pName, &SimpleAnimations[i]);

			for (size_t i = 0; i < token.m_ComplexStartIdx; i++)
				Animations.insert(ComplexAnimations[i].GetAnimationDef()->pName, &ComplexAnimations[i]);

			return token;
		}

		void ResisterAnimations(const AnimationResContainer::ResData& in_rData)
		{
			auto& anims = in_rData.pFile->pAnimations;
			for (size_t i = 0; i < anims->SimpleAnimations.Count; ++i)
			{
				SimpleAnimations[i].Setup(*pAllocator, anims->SimpleAnimations.pAnimations[i], in_rData.SimpleAnimations[i]);
				Animations.insert(anims->SimpleAnimations.pAnimations[i].pName, &SimpleAnimations[i]);
			}

			size_t cmplxOff{};
			for (size_t i = 0; i < anims->ComplexAnimations.Count; ++i)
			{
				ComplexAnimations[i].Setup(*pAllocator, anims->m_ComplexAnimations.pAnimations[i], in_rData.ComplexAnimations, cmplxOff);
				Animations.insert(anims->m_ComplexAnimations.pAnimations[i].pName, &ComplexAnimations[i]);

				cmplxOff += anims->ComplexAnimations.pAnimations[i].Animations.Count;
			}
		}

		void ResisterAnimationsExtend(const AnimationResContainer::ResData& in_rData, const ExtendToken& in_rToken)
		{
			auto& anims = in_rData.pFile->pAnimations;

			size_t idx{};
			for (size_t i = in_rToken.SimpleStartIdx; i < SimpleAnimations.size(); ++i)
			{
				SimpleAnimations[i].Setup(*pAllocator, anims->SimpleAnimations.pAnimations[idx], in_rData.SimpleAnimations[idx]);
				Animations.insert(anims->SimpleAnimations.pAnimations[idx].pName, &SimpleAnimations[i]);
				++idx;
			}

			idx = 0;
			size_t cmplxOff{};
			for (size_t i = in_rToken.ComplexStartIdx; i < ComplexAnimations.size(); ++i)
			{
				ComplexAnimations[i].Setup(*pAllocator, anims->ComplexAnimations.pAnimations[idx], in_rData.ComplexAnimations, cmplxOff);
				Animations.insert(anims->ComplexAnimations.pAnimations[idx].pName, &ComplexAnimations[i]);

				cmplxOff += anims->ComplexAnimations.pAnimations[idx].Animations.Count;
			}
		}

		void Cleanup()
		{
			for (auto& anim : SimpleAnimations)
			{
				anim.Cleanup();
				anim.ProcEvent(AnimationNode::eEvent_FinishCleanup);
			}

			for (auto& anim : ComplexAnimations)
			{
				anim.Cleanup();
				anim.ProcEvent(AnimationNode::eEvent_FinishCleanup);
			}

			if (!SimpleAnimations.empty())
				SimpleAnimations.clear();

			if (!ComplexAnimations.empty())
				ComplexAnimations.clear();
		}

		void SetExternal(ExternalAnimtion* in_pAnim)
		{
			ut::RefPtr rpAnim = in_pAnim;
			m_ExternalAnimations.push_back(rpAnim);

			auto* pClip = in_pAnim->GetSimpleAnimation();
			pClip->pManager = this;
			pClip->pOwner = pOwner;
			pClip->ProcEvent(AnimationNode::eEvent_AttachExternal);
		}
		
		AnimationClip* GetAnimationClip(const char* in_pName) const
		{
			const auto result = m_Animations.find(in_pName);
			if (result == m_Animations.end())
				return nullptr;

			return result;
		}

		struct ExtendToken
		{
			size_t SimpleStartIdx{};
			size_t ComplexStartIdx{};
		};
	};
}