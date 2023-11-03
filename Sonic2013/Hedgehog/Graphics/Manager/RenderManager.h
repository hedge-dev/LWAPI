#pragma once

namespace Extra::fx
{
	struct AmbientParamLightField;

	// TODO: Is this correct?
	struct SLocalLightElement
	{
		csl::math::Vector4 Color{};
		csl::math::Vector4 Radius{};
		csl::math::Vector4 Position{};
	};
}

namespace app::gfx
{
	class CRMSceneViewImpl
	{
	public:
		INSERT_PADDING(22864) {};
		Extra::fx::SLocalLightElement LocalLights[256]{}; // Extra::fx::CArrayContainer<SLocalLightElement, 256>
		INSERT_PADDING(78992) {};
	};

	class CRenderSceneView : public fnd::ReferencedObject
	{
	public:
		INSERT_PADDING(4) {}; // CRenderSceneViewImpl* pImpl{};
		INSERT_PADDING(114160){};

		CRenderSceneView()
		{
			sizeof(CRMSceneViewImpl);
		}
	};

	class RenderManager : public fnd::ReferencedObject, public csl::fnd::SingletonPointer<RenderManager>
	{
		class Impl
		{
		public:
			INSERT_PADDING(114384){};
			CRenderSceneView** pDefaultScene{};
			INSERT_PADDING(8);
			CRMSceneViewImpl* pDefaultSceneImpl{};
			INSERT_PADDING(48){};

			Impl()
			{
				ASSERT_OFFSETOF(Impl, pDefaultScene, 0x1BED0);
				ASSERT_OFFSETOF(Impl, pDefaultSceneImpl, 0x1BEDC);
			}
		};
		
	public:
		Impl* pImpl{};
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
		inline static FUNCTION_PTR(ushort, __thiscall, ms_fpAddLocalLight, ASLR(0x004E4190), RenderManager*, const csl::math::Vector3&, const csl::math::Vector4&, float, float, float, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveLocalLight, ASLR(0x004E1CF0), RenderManager*, ushort);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalLightColor, ASLR(0x004E6020), RenderManager*, ushort, const csl::math::Vector4&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalLightPosition, ASLR(0x004E5FA0), RenderManager*, ushort, const csl::math::Vector3&);
		
		RenderManager()
		{
			
		}

		hh::mr::CRenderingInfrastructure* GetRenderingDevice() const
		{
			return ms_fpGetRenderingDevice(this);
		}

		app::gfx::CRenderSceneView* GetDefaultScene() const
		{
			return *pImpl->pDefaultScene;
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

		ushort AddLocalLight(const csl::math::Vector3& in_rPosition, const csl::math::Vector4& in_rColor, float in_unk1, float in_unk2, float in_unk3, float in_unk4)
		{
			return ms_fpAddLocalLight(this, in_rPosition, in_rColor, in_unk1, in_unk2, in_unk3, in_unk4);
		}

		void RemoveLocalLight(ushort in_lightNo)
		{
			ms_fpRemoveLocalLight(this, in_lightNo);
		}

		void SetLocalLightColor(ushort in_unk, const csl::math::Vector4& in_rColor)
		{
			ms_fpSetLocalLightColor(this, in_unk, in_rColor);
		}

		void SetLocalLightPosition(ushort in_unk, const csl::math::Vector3& in_rPosition)
		{
			ms_fpSetLocalLightPosition(this, in_unk, in_rPosition);
		}

		void SetLocalLightRadius(ushort in_lightId, float in_unk2, float in_unk3, float in_unk4, float in_radius)
		{
			// GetDefaultScene()->pImpl->LightElements.GetByIDTag(in_lightId)->Unk1 = csl::math::Vector4(in_unk2, in_unk3, in_unk3, in_radius);
			// Where the LightElements' type is Extra::fx::CArrayContainer<Extra::fx::SLocalLightElement, 256>
			// and GetByIDTag(ushort in_lightId) returns an SLocalLightElement type.

			pImpl->pDefaultSceneImpl->LocalLights[in_lightId].Radius = { in_unk2, in_unk3, in_unk3, in_radius };
		}
	};
}

DEFINE_SINGLETONPTR(app::gfx::RenderManager, ASLR(0x00FD3CC4));