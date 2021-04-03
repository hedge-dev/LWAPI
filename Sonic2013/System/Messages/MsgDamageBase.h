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
		
	protected:
		fnd::Handle<game::ColliShape> m_SenderShape{};
		fnd::Handle<game::ColliShape> m_RecieverShape{};

	public:
		EnumSenderType m_SenderType{};
		int m_Unk1{};
		csl::math::Vector3 m_Unk2;
		csl::math::Vector3 m_Unk3;
		uint m_Unk4{ static_cast<uint>(-1) };
		BonusData m_Bonus{};
		
		MsgDamageBase(uint id) : fnd::Message(id)
		{
			
		}
	};
}