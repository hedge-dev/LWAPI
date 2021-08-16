#pragma once

namespace app::Player
{
	class CVisualGOC;
	class GOCReferenceHolder;
	class CPlayer;
	class EffectList;
	class CVisualUnit;

	class CVisualBase
	{
	protected:
		CPlayer* m_pOwner{};
		CVisualGOC* m_pVisual{};
		game::GOCSound* m_pSound{};

	public:
		virtual ~CVisualBase() = default;
	};
}