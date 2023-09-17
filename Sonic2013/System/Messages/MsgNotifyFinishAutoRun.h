#pragma once

namespace app::xgame
{
	class MsgNotifyFinishAutoRun : public fnd::Message
	{
	public:
		// There are no references to this message being created, or processed, thus we don't know its ID.
		// To ensure that it falls out of the valid message range no matter what we set the ID to UINT_MAX.
		inline const static unsigned int MessageID = UINT_MAX;

		// There's no vftable left for this message type in the game, which in turn means we don't know the size of the class.

		MsgNotifyFinishAutoRun() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgNotifyFinishAutoRun(*this);
		}
	};
}