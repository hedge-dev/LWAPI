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
		fnd::Handle<game::PathComponent> PathComponent{};
		float Unk1{};
		float Unk2{};
		bool Unk3{};
		csl::ut::Bitset<uint8> Flags{};

		inline const static unsigned int MessageID = 0x5067;

		MsgPLStartAlongPathMode() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLStartAlongPathMode(*this);
		}
	};
}