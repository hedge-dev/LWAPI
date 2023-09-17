#pragma once

namespace app::xgame
{
	class MsgBeltConveyorControlStart : public fnd::Message
	{
	public:
		bool Unk1{};
		int Unk2{};
		csl::math::Vector3 Unk3{};
		csl::math::Vector3 Unk4{};
		float Unk5{};
		GameObjectHandle<GameObject> Unk6{};
		
		inline const static unsigned int MessageID = 0x60AA;

		MsgBeltConveyorControlStart() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgBeltConveyorControlStart(*this);
		}
	};
}