#pragma once

namespace app::xgame
{
	class MsgSetLoopFilter : public fnd::Message
	{
	public:
		bool Unk1{};
		bool Unk2{};

		inline const static unsigned int MessageID = 0x6070;

		MsgSetLoopFilter() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgSetLoopFilter(*this);
		}
	};
}