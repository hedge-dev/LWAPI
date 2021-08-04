#pragma once

namespace app::Camera
{
	struct EnterEventArgs;
	struct SPlayer3DCameraParam;
	struct SPlayer3DCameraParamDashMode;
	
	class CCameraController : public hh::base::CRefCountObject
	{
	protected:
		void* m_pUnk1{}; // Owner?
	
	public:
		float m_Fovy{ 45 };

	protected:
		csl::math::Vector3 m_Position{};
		csl::math::Vector3 m_Up{};
		csl::math::Vector3 m_TargetPosition{};

	public:
		void* m_Unk2{};
		csl::fnd::IAllocator* m_pDebugAlloc{ app::dbg::GetMemoryAllocator() };
		csl::math::Vector2 m_Unk3{};
		bool m_Unk4{};
	
	protected:
		bool m_Active{};
		csl::ut::Bitset<uint> m_Flags{};
	
	public:
		CCameraController()
		{
			
		}

		void SetActive(bool value)
		{
			m_Active = value;
		}

		void SetFovy(float value)
		{
			m_Fovy = value;
		}
		
		virtual void ResetCamera(const csl::math::Vector3& rPos, const csl::math::Vector3& rTargetPos) {}
		virtual void RestartCamera() {}
		virtual void Update(const app::fnd::SUpdateInfo& rInfo) {}
		virtual void OnEnter(const EnterEventArgs& rArgs) { SetActive(true); }
		virtual void OnLeave() { SetActive(false); }

		// bruh
		virtual void BeginBoostCamera() { }
		virtual void EndBoostCamera() { }
		virtual void BeginQuickStep() { }
		virtual void EndQuickStep() { }
		virtual void Set3DCameraParam(const SPlayer3DCameraParam& rParam) { }
		virtual void Set3DCameraParamDashMode(const SPlayer3DCameraParamDashMode& rParam) { }
		virtual void SetCameraReset(const csl::math::Vector3& rPos, const csl::math::Vector3& rTargetPos) {}
		virtual bool IsDistFar() { return false; }
		virtual void FocusChange() { }
		virtual bool ProcessMessage(fnd::Message& rMsg) { return false; }
	};
}