#pragma once

namespace app::xgame
{
	class MsgDroppingSand : public fnd::Message
	{
	public:
		csl::math::Vector3 Unk1{};

		inline const static unsigned int MessageID = 0x6067;

		MsgDroppingSand() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgDroppingSand(*this);
		}
	};
}