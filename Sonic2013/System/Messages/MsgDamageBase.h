#pragma once

namespace app::game
{
	class ColliShape;
}

namespace app::xgame
{
	class MsgDamageBase : public fnd::Message
	{
	public:
		typedef int EnumSenderType;
		struct BonusData
		{
			uint Unk1{ static_cast<uint>(-1) }; // Bonus type?
			uint Bonus{};
		};
		
		fnd::Handle<game::ColliShape> SenderShape{};
		fnd::Handle<game::ColliShape> RecieverShape{};
		EnumSenderType SenderType{};
		uint DefensePower{};
		csl::math::Vector3 Unk2;
		csl::math::Vector3 Unk3;
		uint PlayerNo{ static_cast<uint>(-1) };
		BonusData Bonus{};
		
		MsgDamageBase(uint in_id) : fnd::Message(in_id)
		{

		}
	};
}