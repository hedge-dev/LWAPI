#pragma once

namespace app::xgame
{
	class MsgDroppingSand : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6067;

		csl::math::Vector3 Unk1{};

		MsgDroppingSand() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgDroppingSand(*this);
		}
	};
}