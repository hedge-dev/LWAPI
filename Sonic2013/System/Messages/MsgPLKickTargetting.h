#pragma once

namespace app::xgame
{
	class MsgPLKickTargetting : public fnd::Message
	{
	public:
		game::ColliShape* pOther{};
		game::ColliShape* pSelf{};
		csl::math::Vector3 ContactPosition{};
		size_t PlayerNo{};
		bool Success{};
		
		inline const static unsigned int MessageID = 0x509F;
		
		MsgPLKickTargetting() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgPLKickTargetting(*this);
		}
	};
}