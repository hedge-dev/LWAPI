#pragma once

namespace app::gfx
{
	class RenderManager : public fnd::ReferencedObject, csl::fnd::SingletonPointer<RenderManager>
	{
		class Impl;
		
	protected:
		Impl* m_pImpl{};
		INSERT_PADDING(114448){};
		
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetEnableRenderHud, ASLR(0x004E1D50), RenderManager* pThis, bool enabled);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetFxParameter, ASLR(0x004E4240), RenderManager* pThis, const app::FxParameter& rParameter);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetFxConfig, ASLR(0x004DFF00), RenderManager* pThis, const app::FxSceneConfig& rConfig);
		inline static FUNCTION_PTR(Render::CameraParam&, __thiscall, ms_fpGetCameraParam, ASLR(0x004E1E10), const RenderManager* pThis, int camera);
		
		RenderManager()
		{
			
		}

		void SetEnableRenderHud(bool enabled)
		{
			ms_fpSetEnableRenderHud(this, enabled);
		}

		void SetFxParameter(const app::FxParameter& rParameter)
		{
			ms_fpSetFxParameter(this, rParameter);
		}

		void SetFxConfig(const app::FxSceneConfig& rConfig)
		{
			ms_fpSetFxConfig(this, rConfig);
		}

		const Render::CameraParam& GetCameraParam(int camera) const
		{
			return ms_fpGetCameraParam(this, camera);
		}
	};
}

DEFINE_SINGLETONPTR(app::gfx::RenderManager, ASLR(0x00FD3CC4));