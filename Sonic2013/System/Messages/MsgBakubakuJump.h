#pragma once

namespace app::xgame
{
	class MsgBakubakuJump : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x60D9;

		csl::math::Vector3 Position{};
		csl::math::Vector3 Velocity{};

		MsgBakubakuJump() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgBakubakuJump(*this);
		}
	};
}