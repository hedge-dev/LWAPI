#pragma once

namespace app::game
{
	class ColliShape;
}

namespace app::xgame
{
	class MsgStartKick : public fnd::Message
	{
	public:
		const game::ColliShape* pOther{};
		const game::ColliShape* pSelf{};
		csl::math::Vector3 ContactPosition{};
		csl::math::Vector3 ContactNormal{};
		bool Unk1{};

		inline const static unsigned int MessageID = 0x50B7;

		MsgStartKick(const game::ColliShape* in_pOther, const game::ColliShape* in_pSelf, const csl::math::Vector3& in_rContactPosition, const csl::math::Vector3& in_rContactNormal)
			: Message(MessageID)
			, pOther(in_pOther)
			, pSelf(in_pSelf)
			, ContactPosition(in_rContactPosition)
			, ContactNormal(in_rContactNormal)
		{

		}

		Message* Clone() override
		{
			return new MsgStartKick(*this);
		}
	};
}