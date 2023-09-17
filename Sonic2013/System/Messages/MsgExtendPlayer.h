#pragma once

namespace app::xgame
{
	class MsgExtendPlayer : public fnd::Message
	{
	public:
		Game::EUser User{};
		int LifeCount{};

		inline const static unsigned int MessageID = 0x300F;

		MsgExtendPlayer(Game::EUser in_user, int in_unk) : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgExtendPlayer(*this);
		}
	};
}