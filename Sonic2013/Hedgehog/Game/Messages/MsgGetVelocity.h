#pragma once

namespace app::xgame
{
	class alignas(16) MsgGetVelocity : public fnd::Message
	{
	private:
		const csl::math::Vector3* velocity = csl::math::Vector3::Zero;

	public:
		inline static unsigned int MessageID = 0x2004;

		MsgGetVelocity() : Message(MessageID)
		{
			ASSERT_OFFSETOF(MsgGetVelocity, velocity, 0x18);
		}

		[[nodiscard]] const csl::math::Vector3& GetVelocity() const { return *velocity; }

		void SetVelocity(const csl::math::Vector3& vel)
		{
			velocity = new const csl::math::Vector3(vel);
		}

		Message* Clone() override
		{
			auto* msg = new MsgGetVelocity(*this);
			msg->SetVelocity(msg->GetVelocity());
			return msg;
		}
	};
}
