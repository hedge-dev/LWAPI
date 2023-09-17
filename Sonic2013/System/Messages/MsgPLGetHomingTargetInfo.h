#pragma once

namespace app::xgame
{
	class MsgPLGetHomingTargetInfo : public fnd::Message
	{
	public:
		csl::ut::Bitset<uint> m_Flags{};
		csl::math::Vector3 m_CursorPosition{};
		GameObject* pUnk1{};
		size_t TargetShapeID{};
		size_t m_LockonCount{ 1 };
		int Unk2{};
		const game::ColliShape* pTargetShape{};
		
		inline const static unsigned int MessageID = 0x5004;
		
		MsgPLGetHomingTargetInfo(const game::ColliShape* in_pTargetShape) : Message(MessageID), pTargetShape(in_pTargetShape), TargetShapeID(in_pTargetShape->m_ID)
		{
			
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