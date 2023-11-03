#pragma once

namespace app::fnd
{
	typedef size_t UpdatingPhase;

	struct SUpdateInfo
	{
		float DeltaTime;
		uint Frame;
	};

	class Message
	{
	protected:
		uint m_ID{};

	public:
		uint Sender{};
		uint Receiver{};
		char Handled{};
		bool Broadcasted{};
		const uint Mask{ (uint)-1 };
		
		Message(uint in_id)
		{
			m_ID = in_id;
		}

		uint GetType() const
		{
			return m_ID;
		}
		
		virtual Message* Clone()
		{
			return new Message(m_ID);
		}

		virtual ~Message() = default;

		template <typename T>
		[[nodiscard]] bool IsOfType() const
		{
			static_assert(std::is_base_of<Message, T>(), "Type must be base of app::fnd::Message");
			return m_ID == T::MessageID;
		}

		[[nodiscard]] bool IsBroadcast()
		{
			return Broadcasted;
		}
		
		inline void* operator new(size_t in_size)
		{
			return __HH_ALLOC(in_size);
		}

		inline void operator delete(void* in_pMem)
		{
			__HH_FREE(in_pMem);
		}
	};
}
