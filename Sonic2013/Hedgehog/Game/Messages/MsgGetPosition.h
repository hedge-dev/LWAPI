#pragma once

namespace app::xgame
{
	class alignas(16) MsgGetPosition : public fnd::Message
	{
	private:
		const csl::math::Vector3* position = csl::math::Vector3::Zero;

	public:
		inline static unsigned int MessageID = 0x2003;

		MsgGetPosition() : Message(MessageID)
		{
			ASSERT_OFFSETOF(MsgGetPosition, position, 0x18);
		}

		[[nodiscard]] const csl::math::Vector3& GetPosition() const { return *position; }

		void SetPosition(const csl::math::Vector3& pos)
		{
			position = new const csl::math::Vector3(pos);
		}

		Message* Clone() override
		{
			auto* msg = new MsgGetPosition(*this);
			msg->SetPosition(msg->GetPosition());
			return msg;
		}
	};
}
