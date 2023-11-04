#pragma once

namespace app::xgame
{
	class MsgChange3DMode : public MsgChangeModeBase
	{
	public:
		bool Unk2{};

		inline const static unsigned int MessageID = 0x6010;

		MsgChange3DMode(uint in_unk1, bool in_unk2) : MsgChangeModeBase(MessageID, in_unk1), Unk2(in_unk2)
		{

		}
		
		Message* Clone() override
		{
			return new MsgChange3DMode(*this);
		}
	};
}