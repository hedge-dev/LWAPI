#pragma once

namespace app::xgame
{
	class MsgGetRedRing : public fnd::Message
	{
	public:
		size_t RedRingNo{};
		
		inline const static unsigned int MessageID = 0x6030;
		
		MsgGetRedRing(size_t in_redRingNo) : Message(MessageID), RedRingNo(in_redRingNo)
		{

		}

		Message* Clone() override
		{
			return new MsgGetRedRing(*this);
		}
	};
}