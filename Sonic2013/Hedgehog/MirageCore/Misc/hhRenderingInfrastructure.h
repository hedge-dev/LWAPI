#pragma once

namespace hh::mr
{
	inline static FUNCTION_PTR(boost::shared_ptr<CPixelShaderData>&, __cdecl, fpGetMiragePixelShaderDataFromPackfile, ASLR(0x00C2C1E0), boost::shared_ptr<CPixelShaderData>& ret, const hh::ut::PackFile&, const char*);
	inline static FUNCTION_PTR(boost::shared_ptr<CVertexShaderData>&, __cdecl, fpGetMirageVertexShaderDataFromPackfile, ASLR(0x00C2BF10), boost::shared_ptr<CVertexShaderData>& ret, const hh::ut::PackFile&, const char*);

	inline static boost::shared_ptr<CPixelShaderData> GetMiragePixelShaderDataFromPackfile(const ut::PackFile& in_pac, const char* in_pName)
	{
		boost::shared_ptr<CPixelShaderData> ret{};
		fpGetMiragePixelShaderDataFromPackfile(ret, in_pac, in_pName);	
		return ret;
	}

	inline static boost::shared_ptr<CVertexShaderData> GetMirageVertexShaderDataFromPackfile(const ut::PackFile& in_pac, const char* in_pName)
	{
		boost::shared_ptr<CVertexShaderData> ret{};
		fpGetMirageVertexShaderDataFromPackfile(ret, in_pac, in_pName);
		return ret;
	}

	class CRenderingInfrastructure : public base::CObject
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGetScreenInfo, ASLR(0x00C2BBF0), CRenderingInfrastructure*, uint32_t&, uint32_t&, hh::rsdx::_RSDXFORMAT&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetShaderFromPool, ASLR(0x00C2B330), CRenderingInfrastructure*, CRenderingDevice*, ShaderType);
		inline static FUNCTION_PTR(HRESULT, __thiscall, ms_fpCreateVertexDeclaration, ASLR(0x00C2BED0), CRenderingInfrastructure*, const rsdx::_D3DVERTEXELEMENT9*, hh::mr::CVertexDeclarationPtr*, const hhUchar*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpReleaseVertexDeclaration, ASLR(0x00C2BD70), CRenderingInfrastructure*, rsdx::RsdxVertexDeclaration9**);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddRefVertexDeclaration, ASLR(0x00C2BD80), CRenderingInfrastructure*, rsdx::RsdxVertexDeclaration9**);

		virtual ~CRenderingInfrastructure() = default;

		INSERT_PADDING(0x5C);
		CRenderingDevice m_RenderingDevice;

		CRenderingInfrastructure()
		{
			ASSERT_OFFSETOF(CRenderingInfrastructure, m_RenderingDevice, 0x60);
		}

		void GetScreenInfo(uint32_t& out_width, uint32_t& out_height, hh::rsdx::_RSDXFORMAT& format)
		{
			ms_fpGetScreenInfo(this, out_width, out_height, format);
		}

		void SetShaderFromPool(CRenderingDevice* in_pDevice, ShaderType in_type)
		{
			ms_fpSetShaderFromPool(this, in_pDevice, in_type);
		}

		HRESULT CreateVertexDeclaration(const rsdx::_D3DVERTEXELEMENT9* in_pElements, CVertexDeclarationPtr* out_pDecl, const hhUchar* a3 = nullptr)
		{
			return ms_fpCreateVertexDeclaration(this, in_pElements, out_pDecl, a3);
		}

		void AddRefVertexDeclaration(rsdx::RsdxVertexDeclaration9** in_ppDecl)
		{
			ms_fpAddRefVertexDeclaration(this, in_ppDecl);
		}

		void ReleaseVertexDeclaration(rsdx::RsdxVertexDeclaration9** in_ppDecl)
		{
			ms_fpReleaseVertexDeclaration(this, in_ppDecl);
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