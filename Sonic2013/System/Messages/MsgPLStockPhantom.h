#pragma once

namespace app::xgame
{
	class MsgPLStockPhantom : public fnd::Message
	{
	public:
		Game::EUser User{};
		Game::EPhantomType Type{};

		inline const static unsigned int MessageID = 0x5018;

		MsgPLStockPhantom(Game::EUser in_user, Game::EPhantomType in_type)
			: Message(MessageID)
			, User(in_user)
			, Type(in_type)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLStockPhantom(*this);
		}
	};
}