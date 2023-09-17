#pragma once

namespace app::xgame
{
	class MsgItemTreeWobblePoint : public fnd::Message
	{
	public:
		csl::math::Vector3 WobblePoint{};

		inline const static unsigned int MessageID = 0x604F;

		MsgItemTreeWobblePoint() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgItemTreeWobblePoint(*this);
		}
	};
}