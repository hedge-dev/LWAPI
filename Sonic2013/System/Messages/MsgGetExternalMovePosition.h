#pragma once

namespace app::xgame
{
	class MsgGetExternalMovePosition : public fnd::Message
	{
	public:
		csl::math::Matrix34* pTrsMatrix{};
		
		inline const static unsigned int MessageID = 0x500D;
		
		MsgGetExternalMovePosition() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgGetExternalMovePosition(*this);
		}
	};
}