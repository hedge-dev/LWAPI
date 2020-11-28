#pragma once

#include <type_traits>

namespace app::fnd
{
	typedef size_t UpdatingPhase;

	struct SUpdateInfo
	{
		float deltaTime;
		unsigned int frame;
	};

	class Message
	{
	protected:
		unsigned int id;

	public:
		unsigned int sender;
		unsigned int receiver;
		unsigned short unk1;
		unsigned int mask;
		
		Message(unsigned int id_)
		{
			id = id_;
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
	};
}
