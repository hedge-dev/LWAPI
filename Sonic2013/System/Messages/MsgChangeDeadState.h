#pragma once

namespace app::Player
{
	class MsgChangeDeadState : public fnd::Message
	{
	public:
		const csl::math::Vector3* Unk1{};

		inline const static unsigned int MessageID = 0x50AB;

		MsgChangeDeadState(const csl::math::Vector3& in_rVector) : Message(MessageID), Unk1(&in_rVector)
		{
			
		}

		Message* Clone() override
		{
			return new MsgChangeDeadState(*this);
		}
	};
}