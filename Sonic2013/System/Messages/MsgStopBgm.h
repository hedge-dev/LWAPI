#pragma once

namespace app::xgame
{
	class MsgStopBgm : public fnd::Message
	{
	public:
		float Unk1{};
		size_t Unk2{};

		inline const static unsigned int MessageID = 0xD001;
		
		MsgStopBgm() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgStopBgm(*this);
		}
	};
}