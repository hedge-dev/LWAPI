#pragma once

namespace app::xgame
{
	class alignas(16) MsgDamage : public MsgDamageBase
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004D8500), MsgDamage*, EnumSenderType, uint, uint, const csl::math::Vector3&, const csl::math::Vector3&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor2, ASLR(0x004D8580), MsgDamage*, EnumSenderType, uint, uint, const MsgHitTriggerBase&, const csl::math::Vector3&);

	public:
		size_t AttackType;
		uint Damage{ 1 };
		INSERT_PADDING(8) {};
		csl::math::Vector3 DamagePos{};
		csl::math::Vector3 Unk2{};
		csl::ut::Bitset<uint> ReplyStatus{};
		
		inline const static unsigned int MessageID = 0x4001;
		
		MsgDamage(EnumSenderType in_senderType, uint in_a3, uint in_a4, const csl::math::Vector3& in_pos1, const csl::math::Vector3& in_pos2) : MsgDamageBase(MessageID)
		{
			ms_fpCtor(this, in_senderType, in_a3, in_a4, in_pos1, in_pos2);
		}
		
		MsgDamage(EnumSenderType in_senderType, uint in_a3, uint in_a4, const MsgHitTriggerBase& in_rHitTriggerMsg, const csl::math::Vector3& in_pos2) : MsgDamageBase(MessageID)
		{
			ms_fpCtor2(this, in_senderType, in_a3, in_a4, in_rHitTriggerMsg, in_pos2);
		}

		Message* Clone() override
		{
			return new MsgDamage(*this);
		}

		void SetReply(const csl::math::Vector3& in_rDamagePos, bool in_response)
		{
			DamagePos = in_rDamagePos;
			ReplyStatus.set(6);
			ReplyStatus.set(7, in_response);
		}

		void SetReply(const csl::math::Vector3& in_rDamagePos, bool in_response, const csl::math::Vector3 in_rUnk)
		{
			SetReply(in_rDamagePos, in_response);
			Unk2 = in_rUnk;
			ReplyStatus.set(8);
		}

		bool IsComingReply() const
		{
			return ReplyStatus.test(6);
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

	inline bool Any(uint in_type)
	{
		return in_type != 0;
	}
}