#pragma once

namespace app::xgame
{
	class MsgGetRotation : public fnd::Message
	{
	private:
		csl::math::Quaternion* rotation{};
		
	public:
		inline static unsigned int MessageID = 0x2003;

		MsgGetRotation(csl::math::Quaternion& in_rRotation) : Message(MessageID), rotation(&in_rRotation)
		{

		}

		[[nodiscard] ] csl::math::Quaternion& GetRotation() const { return *rotation; }

		void SetRotation(csl::math::Quaternion& in_rRotation)
		{
			*rotation = in_rRotation;
		}

		Message* Clone() override
		{
			auto* msg = new MsgGetRotation(*this);
			msg->SetRotation(GetRotation());
			return msg;
		}
	};
}
