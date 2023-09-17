#pragma once

namespace app::xgame
{
	class MsgChangeBGMVolume : public fnd::Message
	{
	public:
		float Unk1{};
		float Unk2{};

		inline const static unsigned int MessageID = 0xD007;
		
		MsgChangeBGMVolume() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgChangeBGMVolume(*this);
		}
	};
}