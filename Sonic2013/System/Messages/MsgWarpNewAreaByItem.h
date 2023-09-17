#pragma once

namespace app::xgame
{
	class MsgWarpNewAreaByItem : public fnd::Message
	{
	public:
		uint PlayerNo{};
		csl::math::Vector3 Position{};
		int ItemLevel{};
		bool Unk1{};

		inline const static unsigned int MessageID = 0x6062;

		MsgWarpNewAreaByItem() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgWarpNewAreaByItem(*this);
		}
	};
}