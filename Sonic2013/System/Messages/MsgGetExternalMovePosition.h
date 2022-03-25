#pragma once

namespace app::xgame
{
	class MsgGetExternalMovePosition : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x500D;
		
		csl::math::Matrix34* m_pTransform{};
		
		MsgGetExternalMovePosition() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgGetExternalMovePosition(*this);
		}
	};
}