#pragma once

namespace app::xgame
{
	class MsgKekkoBlow : public fnd::Message
	{
	public:
		csl::math::Vector3 Unk1{};

		inline const static unsigned int MessageID = 0x608D;

		MsgKekkoBlow() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgKekkoBlow(*this);
		}
	};
}