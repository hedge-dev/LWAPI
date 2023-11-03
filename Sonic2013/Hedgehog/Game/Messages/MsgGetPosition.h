#pragma once

namespace app::xgame
{
	class alignas(16) MsgGetPosition : public fnd::Message
	{
	private:
		csl::math::Vector3* m_pPosition{};

	public:
		inline static unsigned int MessageID = 0x2000;

		MsgGetPosition(csl::math::Vector3& in_rPosition) : Message(MessageID), m_pPosition(&in_rPosition)
		{
			ASSERT_OFFSETOF(MsgGetPosition, m_pPosition, 0x18);
		}

		[[nodiscard]] csl::math::Vector3& GetPosition() const { return *m_pPosition; }

		void SetPosition(csl::math::Vector3& in_rPosition)
		{
			*m_pPosition = in_rPosition;
		}

		Message* Clone() override
		{
			auto* pMessage = new MsgGetPosition(*this);
			pMessage->SetPosition(pMessage->GetPosition());
			return pMessage;
		}
	};
}
