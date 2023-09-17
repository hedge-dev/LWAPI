#pragma once

namespace app::xgame
{
	class MsgChange2DMode : public MsgChange2DModeBase
	{
	public:
		inline const static unsigned int MessageID = 0x600E;

		MsgChange2DMode() : MsgChange2DModeBase(MessageID)
		{
			
		}
		
		MsgChange2DMode(uint in_unk, const csl::math::Vector3& in_rUnk2, float in_unk3) : MsgChange2DModeBase(MessageID, in_unk, in_rUnk2, in_unk3)
		{

		}

		Message* Clone() override
		{
			return new MsgChange2DMode(*this);
		}
	};
}