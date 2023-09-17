#pragma once

namespace app::xgame
{
	class MsgGetCenterPosition : public fnd::Message
	{
	public:
		csl::math::Vector3* CenterPosition{};
		
		inline const static unsigned int MessageID = 0x2002;

		MsgGetCenterPosition() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgGetCenterPosition(*this);
		}
	};
}