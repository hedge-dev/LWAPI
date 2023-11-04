#pragma once

namespace app::xgame
{
	class MsgWarpOtherSide : public fnd::Message
	{
	public:
		csl::math::Vector3 TargetPosition{};

		inline const static unsigned int MessageID = 0x6065;

		MsgWarpOtherSide() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgWarpOtherSide(*this);
		}
	};
}