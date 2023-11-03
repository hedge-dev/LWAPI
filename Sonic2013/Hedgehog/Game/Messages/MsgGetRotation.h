#pragma once

namespace app::xgame
{
	class MsgGetRotation : public fnd::Message
	{
	private:
		csl::math::Quaternion* m_pRotation{};
		
	public:
		inline static unsigned int MessageID = 0x2003;

		MsgGetRotation(csl::math::Quaternion& in_rRotation) : Message(MessageID), m_pRotation(&in_rRotation)
		{

		}

		[[nodiscard] ] csl::math::Quaternion& GetRotation() const { return *m_pRotation; }

		void SetRotation(csl::math::Quaternion& in_rRotation)
		{
			*m_pRotation = in_rRotation;
		}

		Message* Clone() override
		{
			auto* pMessage = new MsgGetRotation(*this);
			pMessage->SetRotation(pMessage->GetRotation());
			return pMessage;
		}
	};
}
