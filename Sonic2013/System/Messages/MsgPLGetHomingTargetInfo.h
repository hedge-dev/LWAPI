#pragma once

namespace app::xgame
{
	class MsgPLGetHomingTargetInfo : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5004;
		
		csl::ut::Bitset<uint> m_Flags{};
		csl::math::Vector3 m_CursorPosition{ 0, 0, 0 };
		INSERT_PADDING(8){};
		size_t m_LockonCount{ 1 };
		void* m_Unk1{};
		game::ColliShape* m_pShape{ nullptr };
		
		MsgPLGetHomingTargetInfo() : Message(MessageID)
		{
			ASSERT_OFFSETOF(MsgPLGetHomingTargetInfo, m_LockonCount, 56);
			ASSERT_OFFSETOF(MsgPLGetHomingTargetInfo, m_pShape, 64);
		}

		Message* Clone() override
		{
			return new MsgPLGetHomingTargetInfo(*this);
		}

		void SetHandledFlag()
		{
			m_Flags.set(3);
		}
	};
}