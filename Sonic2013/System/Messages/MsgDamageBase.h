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
			uint m_Unk1{ static_cast<uint>(-1) }; // Bonus type?
			uint m_Bonus{};
		};
		
		fnd::Handle<game::ColliShape> m_SenderShape{};
		fnd::Handle<game::ColliShape> m_RecieverShape{};
		EnumSenderType m_SenderType{};
		uint DefensePower{};
		csl::math::Vector3 m_Unk2;
		csl::math::Vector3 m_Unk3;
		uint PlayerNo{ static_cast<uint>(-1) };
		BonusData m_Bonus{};
		
		MsgDamageBase(uint id) : fnd::Message(id)
		{

		}
	};
}