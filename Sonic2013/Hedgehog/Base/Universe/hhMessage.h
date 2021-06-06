#pragma once

namespace app::fnd
{
	typedef size_t UpdatingPhase;

	struct SUpdateInfo
	{
		float deltaTime;
		uint frame;
	};

	class Message
	{
	protected:
		uint m_ID{};

	public:
		uint m_Sender{};
		uint m_Receiver{};
		char m_Unk1{};
		bool m_Broadcasted{};
		const uint mask{ (uint)-1 };
		
		Message(uint id_)
		{
			m_ID = id_;
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
			return m_Broadcasted;
		}
		
		inline void* operator new(size_t size)
		{
			return __HH_ALLOC(size);
		}

		inline void operator delete(void* mem)
		{
			__HH_FREE(mem);
		}
	};
}
