#pragma once

namespace app::xgame
{
	class MsgPLStartDiving : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x502F;

		float Unk1{};
		float Unk2{};
		float Unk3{};
		float Unk4{};

		MsgPLStartDiving() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLStartDiving(*this);
		}
	};
}