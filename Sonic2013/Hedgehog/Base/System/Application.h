#pragma once

#include <d3d9.h>

namespace app
{
	class SyncTimer;

	class Application
	{
	protected:
		virtual ~Application() = default;
		virtual bool CreateDevice() = 0;
		virtual void DestroyDevice() = 0;
		virtual void InitializeBasic() = 0;
		virtual void ShutdownBasic() = 0;
		virtual void InitializeMain() = 0;
		virtual void ShutdownMain() = 0;
		virtual void RunCore(SyncTimer* in_pTimer) = 0;
		
		INSERT_PADDING(0x90) {};
		IDirect3D9Ex* m_pDirect3D{};
		IDirect3DDevice9Ex* m_pDirect3DDevice{};
		INSERT_PADDING(0x44) {};

		Application()
		{
			ASSERT_OFFSETOF(Application, m_pDirect3D, 0x94);
			ASSERT_OFFSETOF(Application, m_pDirect3DDevice, 0x98);
		}

	public:
		[[nodiscard]] IDirect3D9Ex* GetDirect3D() const
		{
			return m_pDirect3D;
		}

		[[nodiscard]] IDirect3DDevice9Ex* GetDirect3DDevice() const
		{
			return m_pDirect3DDevice;
		}
	};
}