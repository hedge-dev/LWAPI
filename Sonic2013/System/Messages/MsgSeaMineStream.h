#pragma once

namespace app::xgame
{
	class MsgSeaMineStream : public fnd::Message
	{
	public:
		csl::math::Vector3 Unk1{};

		inline const static unsigned int MessageID = 0x6076;

		MsgSeaMineStream() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSeaMineStream(*this);
		}
	};
}