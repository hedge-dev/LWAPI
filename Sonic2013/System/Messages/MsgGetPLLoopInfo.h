#pragma once

namespace app::xgame
{
	class MsgGetPLLoopInfo : public fnd::Message
	{
	public:
		bool Unk1{};
		float Unk2{};
		csl::math::Vector3 Unk3{};
		bool Unk4{};

		inline const static unsigned int MessageID = 0x606F;

		MsgGetPLLoopInfo() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgGetPLLoopInfo(*this);
		}
	};
}