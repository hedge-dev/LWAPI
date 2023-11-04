#pragma once

namespace app::game
{
	class ColliShape;
}

namespace app::xgame
{
	class alignas(16) MsgKick : public MsgDamageBase
	{
	public:
		struct Description
		{
			game::ColliShape* pSrcShape{};
			game::ColliShape* pObjShape{};
			csl::math::Vector3 KickDir{ 0, 0, 0 };
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004D8760), MsgKick*, EnumSenderType, const Description&, const csl::math::Vector3&);

	public:
		csl::math::Vector3 KickDirection{ 0, 0, 0 };
		csl::ut::Bitset<uint> ReplyStatus{};
		
		inline const static unsigned int MessageID = 0x4002;
		
		MsgKick(EnumSenderType in_senderType, const Description& in_rDesc, const csl::math::Vector3& in_rDir) : MsgDamageBase(MessageID)
		{
			ms_fpCtor(this, in_senderType, in_rDesc, in_rDir);
		}

		void SetReplyForSucceed()
		{
			ReplyStatus.set(0, 1);
			ReplyStatus.set(2, 1);
		}
	};
}