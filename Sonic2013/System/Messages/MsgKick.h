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
		inline const static unsigned int MessageID = 0x4002;
		struct Description
		{
			game::ColliShape* m_pSrcShape{};
			game::ColliShape* m_pObjShape{};
			csl::math::Vector3 m_kickDir{ 0, 0, 0 };
		};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004D8760), MsgKick*, EnumSenderType, const Description&, const csl::math::Vector3&);
		csl::math::Vector3 m_KickDirection{ 0, 0, 0 };
		csl::ut::Bitset<uint> m_ReplyStatus{};
		
		MsgKick(EnumSenderType senderType, const Description& desc, const csl::math::Vector3& dir) : MsgDamageBase(MessageID)
		{
			ms_fpCtor(this, senderType, desc, dir);
		}
	};
}