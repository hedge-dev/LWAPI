#pragma once

namespace app::xgame
{
	class MsgCameraUpdate : public fnd::Message
	{
	public:
		inline static uint MessageID = 0x8026;
		float m_DeltaTime{};
		
		MsgCameraUpdate(float delta) : Message(MessageID)
		{
			m_DeltaTime = delta;
		}

		Message* Clone() override
		{
			return new MsgCameraUpdate(m_DeltaTime);
		}
	};
}