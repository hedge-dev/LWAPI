#pragma once

namespace app::xgame
{
	class MsgFlipBoostAnytimeBoost : public fnd::Message
	{
	public:
		// There are no references to this message being created, or processed, thus we don't know its ID.
		// To ensure that it falls out of the valid message range no matter what we set the ID to UINT_MAX.
		inline const static unsigned int MessageID = UINT_MAX;

		MsgFlipBoostAnytimeBoost() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgFlipBoostAnytimeBoost(*this);
		}
	};
}