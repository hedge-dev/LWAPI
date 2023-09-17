#pragma once

namespace app::xgame
{
	class MsgGoal : public fnd::Message
	{
	public:
		enum class EFinishType
		{
			eFinishType_Normal,
			eFinishType_FadeToWhite,
			eFinishType_Snowball
		};
		
		bool m_PanCamera{ false };
		EFinishType m_FinishType{ EFinishType::eFinishType_Normal };
		
		inline const static unsigned int MessageID = 0x300A;

		MsgGoal() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgGoal(*this);
		}
	};
}