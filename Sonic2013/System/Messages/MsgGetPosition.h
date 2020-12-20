#pragma once

namespace app::xgame
{
	class MsgGetPosition : public fnd::Message
	{
	private:
		csl::math::Vector3 position{ 0, 0, 0 };

	public:
		inline static unsigned int MessageID = 0x2003;

		MsgGetPosition() : Message(MessageID)
		{

		}

		[[nodiscard]] const csl::math::Vector3& GetPosition() const { return position; }
		void SetPosition(const csl::math::Vector3& pos) { position = pos; }

		Message* Clone() override
		{
			auto* msg = new MsgGetPosition();
			msg->SetPosition(msg->GetPosition());
			return msg;
		}
	};
}
