#pragma once

namespace app::xgame
{
	class MsgGetRotation : public fnd::Message
	{
	private:
		csl::math::Quaternion rotation{0, 0, 0, 0};
		
	public:
		inline static unsigned int MessageID = 0x2003;

		MsgGetRotation() : Message(MessageID)
		{

		}

		const csl::math::Quaternion& GetRotation() const { return rotation; }
		void SetRotation(const csl::math::Quaternion& rot) { rotation = rot; }

		Message* Clone() override
		{
			auto* msg = new MsgGetRotation();
			msg->SetRotation(GetRotation());
			return msg;
		}
	};
}
