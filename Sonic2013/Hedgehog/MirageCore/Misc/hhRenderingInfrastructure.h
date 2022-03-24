#pragma once

namespace hh::mr
{
	inline static FUNCTION_PTR(boost::shared_ptr<CPixelShaderData>&, __cdecl, fpGetMiragePixelShaderDataFromPackfile, ASLR(0x00C2C1E0), boost::shared_ptr<CPixelShaderData>& ret, hh::ut::PackFile&, const char*);
	inline static FUNCTION_PTR(boost::shared_ptr<CVertexShaderData>&, __cdecl, fpGetMirageVertexShaderDataFromPackfile, ASLR(0x00C2BF10), boost::shared_ptr<CVertexShaderData>& ret, hh::ut::PackFile&, const char*);

	inline static boost::shared_ptr<CPixelShaderData> GetMiragePixelShaderDataFromPackfile(ut::PackFile& in_pac, const char* in_pName)
	{
		boost::shared_ptr<CPixelShaderData> ret{};
		fpGetMiragePixelShaderDataFromPackfile(ret, in_pac, in_pName);	
		return ret;
	}

	inline static boost::shared_ptr<CVertexShaderData> GetMirageVertexShaderDataFromPackfile(ut::PackFile& in_pac, const char* in_pName)
	{
		boost::shared_ptr<CVertexShaderData> ret{};
		fpGetMirageVertexShaderDataFromPackfile(ret, in_pac, in_pName);
		return ret;
	}

	class CRenderingInfrastructure : public base::CObject
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetShaderFromPool, ASLR(0x00C2B330), CRenderingInfrastructure*, CRenderingDevice*, ShaderType);
		virtual ~CRenderingInfrastructure() = default;

		INSERT_PADDING(0x5C);
		CRenderingDevice m_RenderingDevice;

		CRenderingInfrastructure()
		{
			ASSERT_OFFSETOF(CRenderingInfrastructure, m_RenderingDevice, 0x60);
		}

		void SetShaderFromPool(CRenderingDevice* in_pDevice, ShaderType in_type)
		{
			ms_fpSetShaderFromPool(this, in_pDevice, in_type);
		}
	};

	class CRenderingInfrastructureInternal
	{
		inline static FUNCTION_PTR(boost::shared_ptr<CPixelShaderData>&, __cdecl, ms_fpGetShaderFromPackfilePS, ASLR(0x00C2EC30), boost::shared_ptr<CPixelShaderData>& ret, hh::ut::PackFile&, const char*);
		inline static FUNCTION_PTR(boost::shared_ptr<CVertexShaderData>&, __cdecl, ms_fpGetShaderFromPackfileVS, ASLR(0x00C2E780), boost::shared_ptr<CVertexShaderData>& ret, hh::ut::PackFile&, const char*);

		inline static boost::shared_ptr<CPixelShaderData> GetShaderFromPackfilePS(ut::PackFile& in_pac, const char* in_pName)
		{
			boost::shared_ptr<CPixelShaderData> ret{};
			ms_fpGetShaderFromPackfilePS(ret, in_pac, in_pName);
			return ret;
		}

		inline static boost::shared_ptr<CVertexShaderData> GetShaderFromPackfileVS(ut::PackFile& in_pac, const char* in_pName)
		{
			boost::shared_ptr<CVertexShaderData> ret{};
			ms_fpGetShaderFromPackfileVS(ret, in_pac, in_pName);
			return ret;
		}
	};
}

namespace Extra::fx
{
	struct SShaderPair
	{
		boost::shared_ptr<hh::mr::CVertexShaderData> m_spVertexShader{};
		boost::shared_ptr<hh::mr::CPixelShaderData> m_spPixelShader{};
	};

	inline static void GetShaderFromPackfile(SShaderPair& out_pair, hh::ut::PackFile& in_pac, const char* in_pVtxShaderName, const char* in_pPixelShaderName)
	{
		out_pair.m_spVertexShader = hh::mr::GetMirageVertexShaderDataFromPackfile(in_pac, in_pVtxShaderName);
		out_pair.m_spPixelShader = hh::mr::GetMiragePixelShaderDataFromPackfile(in_pac, in_pPixelShaderName);
	}

	inline static void GetShaderFromPackfile(SShaderPair& out_pair, hh::ut::PackFile& in_pac, const char* in_pShaderName)
	{
		out_pair.m_spVertexShader = hh::mr::GetMirageVertexShaderDataFromPackfile(in_pac, in_pShaderName);
		out_pair.m_spPixelShader = hh::mr::GetMiragePixelShaderDataFromPackfile(in_pac, in_pShaderName);
	}
}