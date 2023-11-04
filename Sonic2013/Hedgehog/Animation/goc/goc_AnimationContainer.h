#pragma once

namespace app::game
{
	class GOCAnimationContainer : public GOCAnimation
	{
	private:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7550));

	public:
		struct Description
		{
			size_t AnimCount;
		};
		
	protected:
		csl::ut::InplaceMoveArray<GOCAnimation*, 2> m_Animations{ GetAllocator() };
		
	public:
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
		
		void Setup(const Description& in_rDesc)
		{
			m_Animations.reserve(in_rDesc.AnimCount);
		}

		void Add(GOCAnimation* in_pAnim)
		{
			in_pAnim->AddRef();
			m_Animations.push_back(in_pAnim);
		}

		void Remove(GOCAnimation* in_pAnim)
		{
			if (!in_pAnim)
				return;

			const auto idx = m_Animations.find(in_pAnim);
			if (idx != -1)
				return;

			m_Animations.remove(idx);
			in_pAnim->Release();
		}

		GOCAnimation* Get(size_t in_idx)
		{
			if (in_idx >= m_Animations.size())
				return nullptr;

			return m_Animations[in_idx];
		}
	};
}