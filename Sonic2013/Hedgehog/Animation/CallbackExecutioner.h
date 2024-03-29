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
		CallbackExecutioner(csl::fnd::IAllocator& in_rAlloc) : m_Callbacks(&in_rAlloc), m_SystemCallbacks(&in_rAlloc), m_pAlloc(&in_rAlloc)
		{
			
		}

		void Setup(CharactorAnimation* in_pOwner, size_t in_count)
		{
			m_pOwner = in_pOwner;
			m_Callbacks.resize(in_count);
			m_SystemCallbacks.resize(1);
		}

		void Extend(size_t in_count)
		{
			if (m_Callbacks.size() >= in_count)
				return;

			m_Callbacks.resize(in_count);
		}

		void RegisterCallback(int in_id, AnimationCallback* in_pCallback)
		{
			if (in_id < 0)
			{
				if (m_SystemCallbacks.empty() && in_pCallback)
				{
					delete in_pCallback;
					return;
				}

				m_SystemCallbacks[in_id + 1] = in_pCallback;
			}
			else
			{
				if (m_Callbacks.size() <= in_id && in_pCallback)
				{
					delete in_pCallback;
					return;
				}

				m_Callbacks[in_id] = in_pCallback;
			}
		}

		void UnegisterCallback(int in_id)
		{
			if (in_id < 0)
			{
				auto rpCallback = m_SystemCallbacks[in_id + 1];
				m_SystemCallbacks[in_id + 1] = { nullptr };
			}
			else
			{
				if (m_Callbacks.size() > in_id)
				{
					auto rpCallback = m_Callbacks[in_id];
					m_Callbacks[in_id] = { nullptr };
				}
			}
		}

		void Cleanup()
		{
			m_Callbacks.clear();
			m_SystemCallbacks.clear();

			m_Callbacks.change_allocator(m_pAlloc);
			m_SystemCallbacks.change_allocator(m_pAlloc);
		}
	};
}