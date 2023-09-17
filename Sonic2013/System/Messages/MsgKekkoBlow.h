#pragma once

namespace app::xgame
{
	class MsgKekkoBlow : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x608D;

		csl::math::Vector3 Unk1{};

		MsgKekkoBlow() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgKekkoBlow(*this);
		}
	};
}