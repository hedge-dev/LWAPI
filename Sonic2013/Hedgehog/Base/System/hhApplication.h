#pragma once

class IDirect3D9Ex;
class IDirect3DDevice9Ex;

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
		virtual void RunCore(SyncTimer* timer) = 0;

		INSERT_PADDING(0x90){};
		IDirect3D9Ex* d3d{};
		IDirect3DDevice9Ex* d3dDevice{};
		INSERT_PADDING(0x2C){};
		
		Application()
		{
			ASSERT_OFFSETOF(Application, d3d, 0x94);
			ASSERT_OFFSETOF(Application, d3dDevice, 0x98);
		}

	public:
		[[nodiscard]] IDirect3D9Ex* GetDirect3D() const
		{
			return d3d;
		}

		[[nodiscard]] IDirect3DDevice9Ex* GetDirect3DDevice() const
		{
			return d3dDevice;
		}
	};
}