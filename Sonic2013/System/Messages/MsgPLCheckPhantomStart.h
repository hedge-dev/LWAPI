#pragma once

namespace app::Player
{
	class MsgPLCheckPhantomStart : public fnd::Message
	{
	public:
		Game::EPhantomType Type{};
		int Unk1{};
		int Unk2{ -1 };
		csl::math::Vector3 Unk3{};

		inline const static unsigned int MessageID = 0x50B4;

		MsgPLCheckPhantomStart(Game::EPhantomType in_type) : Message(MessageID), Type(in_type)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLCheckPhantomStart(*this);
		}
	};
}