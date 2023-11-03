#pragma once

namespace app::xgame
{
	class alignas(16) MsgGetVelocity : public fnd::Message
	{
	private:
		const csl::math::Vector3* m_pVelocity = csl::math::Vector3::Zero;

	public:
		inline static unsigned int MessageID = 0x2004;

		MsgGetVelocity() : Message(MessageID)
		{
			ASSERT_OFFSETOF(MsgGetVelocity, m_pVelocity, 0x18);
		}

		[[nodiscard]] const csl::math::Vector3& GetVelocity() const { return *m_pVelocity; }

		void SetVelocity(const csl::math::Vector3& in_rVelocity)
		{
			m_pVelocity = new const csl::math::Vector3(in_rVelocity);
		}

		Message* Clone() override
		{
			auto* pMessage = new MsgGetVelocity(*this);
			pMessage->SetVelocity(pMessage->GetVelocity());
			return pMessage;
		}
	};
}
