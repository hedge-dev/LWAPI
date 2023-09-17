#pragma once

namespace app::xgame
{
	class MsgCheckWarpNewAreaByItem : public fnd::Message
	{
	public:
		uint PlayerNo{};
		csl::math::Vector3 Position{};
		int ItemLevel{};
		bool Unk1{};

		inline const static unsigned int MessageID = 0x6063;

		MsgCheckWarpNewAreaByItem() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgCheckWarpNewAreaByItem(*this);
		}
	};
}