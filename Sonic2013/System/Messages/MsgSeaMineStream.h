#pragma once

namespace app::xgame
{
	class MsgSeaMineStream : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6076;

		csl::math::Vector3 Unk1{};

		MsgSeaMineStream() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSeaMineStream(*this);
		}
	};
}