#pragma once

namespace app::xgame
{
	class MsgCameraUpdate : public fnd::Message
	{
	public:
		float DeltaTime{};
		
		inline const static unsigned int MessageID = 0x8026;

		MsgCameraUpdate(float in_deltaTime) : Message(MessageID)
		{
			DeltaTime = in_deltaTime;
		}

		Message* Clone() override
		{
			return new MsgCameraUpdate(DeltaTime);
		}
	};
}