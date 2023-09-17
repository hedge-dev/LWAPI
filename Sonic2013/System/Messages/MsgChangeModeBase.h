#pragma once

namespace app::xgame
{
	class MsgChangeModeBase : public fnd::Message
	{
	public:
		uint Unk1{};

		MsgChangeModeBase(int in_messageId, uint in_unk2) : Message(in_messageId), Unk1(in_unk2)
		{
			
		}

		Message* Clone() override
		{
			return new MsgChangeModeBase(*this);
		}
	};
}