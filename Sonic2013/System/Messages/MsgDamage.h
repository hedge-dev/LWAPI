#pragma once

namespace app::xgame
{
	class alignas(16) MsgDamage : public MsgDamageBase
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004D8500), MsgDamage*, EnumSenderType senderType, uint a3, uint a4, const csl::math::Vector3& pos1, const csl::math::Vector3& pos2);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor2, ASLR(0x004D8580), MsgDamage*, EnumSenderType senderType, uint a3, uint a4, const MsgHitTriggerBase& , const csl::math::Vector3& pos2);

		size_t AttackType;
		uint m_Damage{ 1 };
		INSERT_PADDING(8) {};
		csl::math::Vector3 m_DamagePos{};
		csl::math::Vector3 Unk2{};
		csl::ut::Bitset<uint> m_ReplyStatus{};
		
		inline const static unsigned int MessageID = 0x4001;
		
		MsgDamage(EnumSenderType senderType, uint a3, uint a4, const csl::math::Vector3& pos1, const csl::math::Vector3& pos2) : MsgDamageBase(MessageID)
		{
			ms_fpCtor(this, senderType, a3, a4, pos1, pos2);
		}
		
		MsgDamage(EnumSenderType senderType, uint a3, uint a4, const MsgHitTriggerBase& in_rHitTriggerMsg, const csl::math::Vector3& pos2) : MsgDamageBase(MessageID)
		{
			ms_fpCtor2(this, senderType, a3, a4, in_rHitTriggerMsg, pos2);
		}

		Message* Clone() override
		{
			return new MsgDamage(*this);
		}

		void SetReply(const csl::math::Vector3& in_rDamagePos, bool in_response)
		{
			m_DamagePos = in_rDamagePos;
			m_ReplyStatus.set(6);
			m_ReplyStatus.set(7, in_response);
		}

		void SetReply(const csl::math::Vector3& in_rDamagePos, bool in_response, const csl::math::Vector3 in_rUnk)
		{
			SetReply(in_rDamagePos, in_response);
			Unk2 = in_rUnk;
			m_ReplyStatus.set(8);
		}

		bool IsComingReply() const
		{
			return m_ReplyStatus.test(6);
		}
	};
}

namespace app::AttackType
{
	typedef size_t EDamagedType;

	inline bool And(uint in_left, uint in_right)
	{
		return (in_left & in_right) != 0;
	}

	inline bool IsDamaged(uint in_left, EDamagedType in_type)
	{
		return (in_left & in_type) == in_type;
	}

	inline bool Any(uint type)
	{
		return type != 0;
	}
}