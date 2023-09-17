#pragma once

namespace app::xgame
{
	class MsgDisableItemBag : public fnd::Message
	{
	public:
		int Unk1{};

		inline const static unsigned int MessageID = 0x302F;
		
		MsgDisableItemBag() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgDisableItemBag(*this);
		}
	};
}