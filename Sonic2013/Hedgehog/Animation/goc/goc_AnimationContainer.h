#pragma once

namespace app::game
{
	class GOCAnimationContainer : public GOCAnimation
	{
	public:
		struct Description
		{
			size_t m_AnimCount;
		};
		
	protected:
		csl::ut::InplaceMoveArray<GOCAnimation*, 2> m_Animations{ GetAllocator() };
		
	public:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7550));

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		~GOCAnimationContainer()
		{
			for (auto& anim : m_Animations)
			{
				anim->Release();
			}
		}
		
		void Setup(const Description& desc)
		{
			m_Animations.reserve(desc.m_AnimCount);
		}

		void Add(GOCAnimation* pAnim)
		{
			pAnim->AddRef();
			m_Animations.push_back(pAnim);
		}

		void Remove(GOCAnimation* pAnim)
		{
			if (!pAnim)
				return;

			const auto idx = m_Animations.find(pAnim);
			if (idx != -1)
				return;

			m_Animations.remove(idx);
			pAnim->Release();
		}

		GOCAnimation* Get(size_t idx)
		{
			if (idx >= m_Animations.size())
				return nullptr;

			return m_Animations[idx];
		}
	};
}