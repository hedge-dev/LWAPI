#pragma once

namespace app::xgame
{
	class MsgEndSign : public fnd::Message
	{
	public:
		typedef int ESignType;

		ESignType Type{};
		bool Unk1{};

		inline const static unsigned int MessageID = 0xC025;

		MsgEndSign(ESignType in_type, bool in_unk) : Message(MessageID), Type(in_type), Unk1(in_unk)
		{
			
		}

		Message* Clone() override
		{
			return new MsgEndSign(*this);
		}
	};
}