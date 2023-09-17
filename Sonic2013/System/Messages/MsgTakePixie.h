#pragma once

namespace app::xgame
{
	class MsgTakePixie : public fnd::Message
	{
	public:
		Game::EPhantomType Type{};
		float Unk1{};
		int ItemLevel{};
		bool Taken{};
		
		inline const static unsigned int MessageID = 0x6019;

		MsgTakePixie(Game::EPhantomType in_type, float in_unk) : Message(MessageID)
		{
			Type = in_type;
			Unk1 = in_unk;
		}

		Message* Clone() override
		{
			return new MsgTakePixie(*this);
		}
	};
}