#pragma once

namespace app::xgame
{
	class alignas(16) MsgGetPosition : public fnd::Message
	{
	private:
		csl::math::Vector3* position{};

	public:
		inline static unsigned int MessageID = 0x2000;

		MsgGetPosition(csl::math::Vector3& in_rPosition) : Message(MessageID), position(&in_rPosition)
		{
			ASSERT_OFFSETOF(MsgGetPosition, position, 0x18);
		}

		[[nodiscard]] csl::math::Vector3& GetPosition() const { return *position; }

		void SetPosition(csl::math::Vector3& in_rPosition)
		{
			*position = in_rPosition;
		}

		Message* Clone() override
		{
			auto* msg = new MsgGetPosition(*this);
			msg->SetPosition(msg->GetPosition());
			return msg;
		}
	};
}
