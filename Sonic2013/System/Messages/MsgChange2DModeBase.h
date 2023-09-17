#pragma once

namespace app::xgame
{
	class MsgChange2DModeBase : public MsgChangeModeBase
	{
	public:
		csl::math::Vector3 Unk2{};
		float Unk3{};
		csl::ut::Bitset<uint> Flags{};
		
		MsgChange2DModeBase(int in_messageId) : MsgChangeModeBase(in_messageId, 0)
		{

		}

		MsgChange2DModeBase(int in_messageId, uint in_unk1, const csl::math::Vector3& in_rUnk2, float in_unk3) : MsgChangeModeBase(in_messageId, in_unk1), Unk2(in_rUnk2), Unk3(in_unk3)
		{
			Flags.set();
			Flags.reset(3);
		}

		Message* Clone() override
		{
			return new MsgChange2DModeBase(*this);
		}
	};
}