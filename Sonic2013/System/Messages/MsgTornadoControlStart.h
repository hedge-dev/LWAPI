#pragma once

namespace app::xgame
{
	class MsgTornadoControlStart : public fnd::Message
	{
		enum ObjectType : uint8;
		enum ActionType : uint8;

	public:
		GameObjectHandle<GameObject> Unk1{};
		csl::ut::Enum<ObjectType, uint8> Unk2{};
		csl::ut::Enum<ActionType, uint8> Unk3{};

		inline const static unsigned int MessageID = 0x605A;

		MsgTornadoControlStart() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgTornadoControlStart(*this);
		}
	};
}