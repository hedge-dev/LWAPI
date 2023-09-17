#pragma once

namespace app::xgame
{
	class MsgGetClimbObjectInfo : public fnd::Message
	{
	public:
		int Unk1{};
		csl::math::Vector3* pPosition{};

		inline const static unsigned int MessageID = 0x6050;

		MsgGetClimbObjectInfo() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgGetClimbObjectInfo(*this);
		}
	};
}