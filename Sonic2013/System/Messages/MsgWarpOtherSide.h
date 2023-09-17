#pragma once

namespace app::xgame
{
	class MsgWarpOtherSide : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6065;

		csl::math::Vector3 TargetPosition{};

		MsgWarpOtherSide() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgWarpOtherSide(*this);
		}
	};
}