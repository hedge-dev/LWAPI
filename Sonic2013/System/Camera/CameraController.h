#pragma once

namespace app::Camera
{
	struct EnterEventArgs;
	struct SPlayer3DCameraParam;
	struct SPlayer3DCameraParamDashMode;
	
	class CCameraController : public hh::base::CRefCountObject
	{
	protected:
		CCamera* m_pOwner{}; // Owner?
	
	public:
		float m_Fovy{ 45 };

	protected:
		csl::math::Vector3 m_Position{};
		csl::math::Vector3 m_Up{};
		csl::math::Vector3 m_TargetPosition{};

	public:
		void* m_Unk1{};
		csl::fnd::IAllocator* m_pDebugAlloc{ app::dbg::GetMemoryAllocator() };
		csl::math::Vector2 m_Unk2{};
		bool m_Unk3{};
	
	protected:
		bool m_Active{};
		csl::ut::Bitset<uint> m_Flags{};
	
	public:
		CCameraController()
		{
			
		}

		bool IsCollisionEnable() const { return m_Flags.test(0); }
		bool IsPhantomCamera() const { return m_Flags.test(1); }
		bool IsDebugCamera() const { return m_Flags.test(2); }
		bool IsMultiCamera() const { return m_Flags.test(3); }
		bool IsPreview() const { return m_Flags.test(4); }

		void SetCollisionEnable(bool flag) { m_Flags.set(0, flag); }
		void SetPhantomCamera(bool flag) { m_Flags.set(1, flag); }
		void SetDebugCamera(bool flag) { m_Flags.set(2, flag); }
		void SetMultiCamera(bool flag) { m_Flags.set(3, flag); }
		void SetPreview(bool flag) { m_Flags.set(4, flag); }

		
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