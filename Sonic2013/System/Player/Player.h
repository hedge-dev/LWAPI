#pragma once

namespace app::Player
{
	struct SCinfo;
	class CPhysics;
	class CStateGOC;
	class CVisualGOC;
	class CBlackBoard;
	class CPathService;
	class SVisualCinfo;
	class CPostureMoveManager;
	class CPostureInputManager;
	class CHomingTargetService;
	
	class CPlayer : public GameObject3D
	{
	public:
		INSERT_PADDING(12) {};
		CGOCCollection<10> m_Components{};
		CPostureInputManager* m_pPostureInputMan{};
		CPostureMoveManager* m_pPostureMoveMan{};
		CPhysics* m_pPhysics{};
		CBlackBoard* m_pBlackboard{};
		ut::ScopedPtr<CPathService> m_spPathService{ nullptr, nullptr };
		ut::ScopedPtr<CHomingTargetService> m_spHomingService{ nullptr, nullptr };
		const SCinfo* m_pCinfo{};
		ut::ScopedPtr<SVisualCinfo> m_spVisualCinfo{nullptr, nullptr};
		size_t m_CameraId{};
		void* m_Unk1{};
		GameObjectHandle<GameObject> m_Vehicle{};
		app::ut::RefPtr<Camera::CCameraController> m_rpCamera{};
		INSERT_PADDING(20) {};
		
		CPlayer()
		{
			
		}

		CStateGOC* GetStateGOC() const
		{
			return m_Components.GetGOC<CStateGOC>();
		}

		CVisualGOC* GetVisualGOC() const
		{
			return m_Components.GetGOC<CVisualGOC>();
		}
	};
}