#pragma once

namespace app::xgame
{
	class MsgTornadoControlAction : public fnd::Message
	{
	public:
		char Unk1{};
		csl::math::Vector3 Unk2{};

		inline const static unsigned int MessageID = 0x605B;

		MsgTornadoControlAction() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgTornadoControlAction(*this);
		}
	};
}