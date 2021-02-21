#pragma once

namespace app
{
	class CGame;
	enum RcType;

	// Size is actually 272 bytes
	class CGameSequence : public fnd::ReferencedObject
	{
	public:
		struct DevData
		{
			csl::ut::FixedString<32> m_Unk1{};
			uint m_Unk2; // Language?
			RcType m_RcType;
			uint m_RcDesign;
			uint m_RcLevel;
			uint m_BattleMode;
			uint m_RingRaceSetNo;
			uint m_MinigameMode;
		};

	protected:
		INSERT_PADDING(44);
		CGame* m_pGame;
		void* m_pUnk1;
		csl::ut::FixedString<16> m_StgId;
		INSERT_PADDING(36);
		DevData* m_pDevData;
		
	public:
		CGameSequence()
		{
			
		}

		DevData* GetDevData() const
		{
			return m_pDevData;
		}
		
		void SetDevData(DevData* pDevData)
		{
			m_pDevData = pDevData;
		}
	};

	enum RcType
	{
		NONE = -1,
		HELICOPTER = 0,
		FIGTHER = 1,
		STEALTH = 2,
		HOVERCRAFT = 3,
		BALLOON = 4,
		UFO = 5,
		OMOCHAO = 6,
	};
}