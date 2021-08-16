#pragma once

namespace app::xgame
{
	class MsgGetRotation : public fnd::Message
	{
	private:
		const csl::math::Quaternion* rotation = &csl::math::Quaternion::Identity;
		
	public:
		inline static unsigned int MessageID = 0x2003;

		MsgGetRotation() : Message(MessageID)
		{

		}

		[[nodiscard] ]const csl::math::Quaternion& GetRotation() const { return *rotation; }

		void SetRotation(const csl::math::Quaternion& rot)
		{
			rotation = new csl::math::Quaternion(rot);
		}

		Message* Clone() override
		{
			auto* msg = new MsgGetRotation(*this);
			msg->SetRotation(GetRotation());
			return msg;
		}
	};
}
