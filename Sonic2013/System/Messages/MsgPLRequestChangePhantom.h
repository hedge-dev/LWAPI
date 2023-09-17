#pragma once

namespace app::xgame
{
	class MsgPLRequestChangePhantom : public fnd::Message
	{
		enum ObjectType : uint8;
		enum ActionType : uint8;

	public:
		char Unk1{};
		int Unk2{};
		bool Changed{};
		
		inline const static unsigned int MessageID = 0x5055;
		
		MsgPLRequestChangePhantom() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLRequestChangePhantom(*this);
		}
	};
}