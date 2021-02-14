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
		uint id;

	public:
		uint sender;
		uint receiver;
		char unk1;
		bool broadcasted;
		const uint mask{ (uint)-1 };
		
		Message(uint id_)
		{
			id = id_;
		}

		uint GetType() const
		{
			return id;
		}
		
		virtual Message* Clone()
		{
			return new Message(id);
		}

		virtual ~Message() = default;

		template <typename T>
		[[nodiscard]] bool IsOfType() const
		{
			static_assert(std::is_base_of<Message, T>(), "Type must be base of app::fnd::Message");
			return id == T::MessageID;
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
