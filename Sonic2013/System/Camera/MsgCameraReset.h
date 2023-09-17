#pragma once

namespace app::xgame
{
	class MsgCameraReset : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x8000;

		MsgCameraReset() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgCameraReset(*this);
		}
	};
}