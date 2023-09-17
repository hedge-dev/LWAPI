#pragma once

namespace app::game
{
	class PathComponent;
}

namespace app::xgame
{
	class MsgPLStartAlongPathMode : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5067;

		fnd::Handle<game::PathComponent> PathComponent{};
		float Unk1{};
		float Unk2{};
		bool Unk3{};
		csl::ut::Bitset<uint8> Flags{};

		MsgPLStartAlongPathMode() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLStartAlongPathMode(*this);
		}
	};
}