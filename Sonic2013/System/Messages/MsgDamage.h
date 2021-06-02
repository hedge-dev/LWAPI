#pragma once

namespace app::xgame
{
	class alignas(16) MsgDamage : public MsgDamageBase
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004D8500), MsgDamage*, EnumSenderType senderType, uint a3, uint a4, const csl::math::Vector3& pos1, const csl::math::Vector3& pos2);
		inline const static unsigned int MessageID = 0x4001;

		size_t m_Unk1;
		uint m_Damage{1};
		INSERT_PADDING(8) {};
		csl::math::Vector3 m_DamagePos{};
		INSERT_PADDING(16){};
		csl::ut::Bitset<uint> m_ReplyStatus{};
		
		MsgDamage(EnumSenderType senderType, uint a3, uint a4, const csl::math::Vector3& pos1, const csl::math::Vector3& pos2) : MsgDamageBase(MessageID)
		{
			ms_fpCtor(this, senderType, a3, a4, pos1, pos2);
		}

		Message* Clone() override
		{
			return new MsgDamage(*this);
		}

		void SetReplyStatus(const csl::math::Vector3& damagePos, bool response)
		{
			m_DamagePos = damagePos;
			m_ReplyStatus.set(6, response);
			m_ReplyStatus.set(7, response);
		}
	};
}