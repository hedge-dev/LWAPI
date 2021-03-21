#pragma once

namespace app::animation
{
	class AnimationCallback;
	class CharactorAnimation;
	
	class CallbackExecutioner
	{
	protected:
		CharactorAnimation* m_pOwner{};
		csl::ut::ObjectMoveArray<ut::RefPtr<AnimationCallback>> m_Callbacks;
		csl::ut::ObjectMoveArray<ut::RefPtr<AnimationCallback>> m_SystemCallbacks;
		csl::fnd::IAllocator* m_pAlloc{};

	public:
		CallbackExecutioner(csl::fnd::IAllocator& rAlloc) : m_Callbacks(&rAlloc), m_SystemCallbacks(&rAlloc), m_pAlloc(&rAlloc)
		{
			
		}

		void RegisterCallback(int id, AnimationCallback* pCallback)
		{
			if (id < 0)
			{
				if (m_SystemCallbacks.empty() && pCallback)
				{
					delete pCallback;
					return;
				}

				m_SystemCallbacks[id] = pCallback;
			}
			else
			{
				if (m_Callbacks.size() <= id && pCallback)
				{
					delete pCallback;
					return;
				}

				m_Callbacks[id] = pCallback;
			}
		}
	};
}