#pragma once

namespace Extra::fx
{
	struct AmbientParamLightField;
}

namespace app::gfx
{
	class RenderManager : public fnd::ReferencedObject, public csl::fnd::SingletonPointer<RenderManager>
	{
		class Impl;
		
	public:
		Impl* m_pImpl{};
		INSERT_PADDING(114448){};

		typedef int eDrcRenderMode;
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetEnableRenderHud, ASLR(0x004E1D50), RenderManager* pThis, bool enabled);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetGameDocument, ASLR(0x004DFF20), RenderManager* pThis, GameDocument*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetDRCRenderMode, ASLR(0x004E5F30), RenderManager* pThis, eDrcRenderMode);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetFxParameter, ASLR(0x004E4240), RenderManager* pThis, const app::FxParameter& rParameter);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetFxConfig, ASLR(0x004DFF00), RenderManager* pThis, const app::FxSceneConfig& rConfig);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddRenderable, ASLR(0x004E1E30), RenderManager* pThis, Renderable* pRenderable);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetLightFieldColor, ASLR(0x004E1D30), const RenderManager* pThis, const csl::math::Vector3&, Extra::fx::AmbientParamLightField& out_param);
		inline static FUNCTION_PTR(hh::ut::PackFile&, __thiscall, ms_fpGetShaderFileResource, ASLR(0x004E6050), const RenderManager* pThis, hh::ut::PackFile&);
		inline static FUNCTION_PTR(hh::mr::CRenderingInfrastructure*, __thiscall, ms_fpGetRenderingDevice, ASLR(0x004E1C10), const RenderManager* pThis);
		inline static FUNCTION_PTR(Render::CameraParam&, __thiscall, ms_fpGetCameraParam, ASLR(0x004E1E10), const RenderManager* pThis, int camera);
		
		RenderManager()
		{
			
		}

		hh::mr::CRenderingInfrastructure* GetRenderingDevice() const
		{
			return ms_fpGetRenderingDevice(this);
		}

		hh::ut::PackFile GetShaderFileResource() const
		{
			hh::ut::PackFile result { nullptr };
			ms_fpGetShaderFileResource(this, result);

			return result;
		}

		bool GetLightFieldColor(const csl::math::Vector3& in_point, Extra::fx::AmbientParamLightField& out_lightfield) const
		{
			return ms_fpGetLightFieldColor(this, in_point, out_lightfield);
		}

		void SetEnableRenderHud(bool in_enabled)
		{
			ms_fpSetEnableRenderHud(this, in_enabled);
		}

		void SetDRCRenderMode(eDrcRenderMode in_mode)
		{
			ms_fpSetDRCRenderMode(this, in_mode);
		}

		void SetFxParameter(const app::FxParameter& in_parameter)
		{
			ms_fpSetFxParameter(this, in_parameter);
		}

		void SetGameDocument(app::GameDocument* in_pDocument)
		{
			ms_fpSetGameDocument(this, in_pDocument);
		}

		void SetFxConfig(const app::FxSceneConfig& in_config)
		{
			ms_fpSetFxConfig(this, in_config);
		}

		const Render::CameraParam& GetCameraParam(int in_camera) const
		{
			return ms_fpGetCameraParam(this, in_camera);
		}

		void AddRenderable(Renderable* in_pRenderable)
		{
			ms_fpAddRenderable(this, in_pRenderable);
		}
	};
}

DEFINE_SINGLETONPTR(app::gfx::RenderManager, ASLR(0x00FD3CC4));