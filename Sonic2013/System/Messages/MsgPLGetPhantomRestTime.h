#pragma once

namespace app::xgame
{
	class MsgPLGetPhantomRestTime : public fnd::Message
	{
	public:
		Game::EPhantomType Type{ static_cast<Game::EPhantomType>(-1) };
		float RestTime{};

		inline const static unsigned int MessageID = 0x505A;

		MsgPLGetPhantomRestTime() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLGetPhantomRestTime(*this);
		}
	};
}