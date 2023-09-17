#pragma once

namespace app::xgame
{
	class MsgRingGetSuckedInto : public fnd::Message
	{
	public:
		int PlayerNo;
		int Unk1;

		inline const static unsigned int MessageID = 0x60B5;

		MsgRingGetSuckedInto() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgRingGetSuckedInto(*this);
		}
	};
}