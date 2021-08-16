#pragma once

namespace app::Player
{
	class StateUtil
	{
	public:
		inline static FUNCTION_PTR(void, __cdecl, ms_fpResetPosition, ASLR(0x008D9C60), CStateGOC&, const csl::math::Vector3&);
		inline static FUNCTION_PTR(void, __cdecl, ms_fpResetPositionAll, ASLR(0x008D85F0), CStateGOC&, const csl::math::Vector3&, const csl::math::Quaternion&);
		
		static void ResetPosition(CStateGOC& rStateGoc, const csl::math::Vector3& rPos)
		{
			ms_fpResetPosition(rStateGoc, rPos);
		}
		
		static void ResetPosition(CStateGOC& rStateGoc, const csl::math::Vector3& rPos, const csl::math::Quaternion& rRot)
		{
			ms_fpResetPositionAll(rStateGoc, rPos, rRot);
		}

		static void ResetPosition(CPlayer& rPlayer, const csl::math::Vector3& rPos)
		{
			auto* pStateGoc = rPlayer.GetStateGOC();

			if (pStateGoc)
				ResetPosition(*pStateGoc, rPos);
		}

		static void ResetPosition(CPlayer& rPlayer, const csl::math::Vector3& rPos, const csl::math::Quaternion& rRot)
		{
			auto* pStateGoc = rPlayer.GetStateGOC();

			if (pStateGoc)
				ResetPosition(*pStateGoc, rPos, rRot);
		}
	};
}