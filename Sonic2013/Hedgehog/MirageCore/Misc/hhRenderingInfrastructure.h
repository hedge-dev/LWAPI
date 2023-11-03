#pragma once

namespace hh::mr
{
	inline static FUNCTION_PTR(boost::shared_ptr<CPixelShaderData>&, __cdecl, fpGetMiragePixelShaderDataFromPackfile, ASLR(0x00C2C1E0), boost::shared_ptr<CPixelShaderData>& ret, const hh::ut::PackFile&, const char*);
	inline static FUNCTION_PTR(boost::shared_ptr<CVertexShaderData>&, __cdecl, fpGetMirageVertexShaderDataFromPackfile, ASLR(0x00C2BF10), boost::shared_ptr<CVertexShaderData>& ret, const hh::ut::PackFile&, const char*);

	inline static boost::shared_ptr<CPixelShaderData> GetMiragePixelShaderDataFromPackfile(const ut::PackFile& in_rPac, const char* in_pName)
	{
		boost::shared_ptr<CPixelShaderData> ret{};
		fpGetMiragePixelShaderDataFromPackfile(ret, in_rPac, in_pName);	
		return ret;
	}

	inline static boost::shared_ptr<CVertexShaderData> GetMirageVertexShaderDataFromPackfile(const ut::PackFile& in_rPac, const char* in_pName)
	{
		boost::shared_ptr<CVertexShaderData> ret{};
		fpGetMirageVertexShaderDataFromPackfile(ret, in_rPac, in_pName);
		return ret;
	}

	class CRenderingInfrastructure : public base::CObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGetScreenInfo, ASLR(0x00C2BBF0), CRenderingInfrastructure*, uint32_t&, uint32_t&, hh::rsdx::_RSDXFORMAT&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetShaderFromPool, ASLR(0x00C2B330), CRenderingInfrastructure*, CRenderingDevice*, ShaderType);
		inline static FUNCTION_PTR(HRESULT, __thiscall, ms_fpCreateVertexDeclaration, ASLR(0x00C2BED0), CRenderingInfrastructure*, const rsdx::_D3DVERTEXELEMENT9*, hh::mr::CVertexDeclarationPtr*, const hhUchar*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpReleaseVertexDeclaration, ASLR(0x00C2BD70), CRenderingInfrastructure*, rsdx::RsdxVertexDeclaration9**);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddRefVertexDeclaration, ASLR(0x00C2BD80), CRenderingInfrastructure*, rsdx::RsdxVertexDeclaration9**);

	public:
		virtual ~CRenderingInfrastructure() = default;

		INSERT_PADDING(0x5C);
		CRenderingDevice RenderingDevice;

		CRenderingInfrastructure()
		{
			ASSERT_OFFSETOF(CRenderingInfrastructure, RenderingDevice, 0x60);
		}

		void GetScreenInfo(uint32_t& out_rWidth, uint32_t& out_rHeight, hh::rsdx::_RSDXFORMAT& in_rFormat)
		{
			ms_fpGetScreenInfo(this, out_rWidth, out_rHeight, in_rFormat);
		}

		void SetShaderFromPool(CRenderingDevice* in_pDevice, ShaderType in_type)
		{
			ms_fpSetShaderFromPool(this, in_pDevice, in_type);
		}

		HRESULT CreateVertexDeclaration(const rsdx::_D3DVERTEXELEMENT9* in_pElements, CVertexDeclarationPtr* out_pDecl, const hhUchar* in_pA3 = nullptr)
		{
			return ms_fpCreateVertexDeclaration(this, in_pElements, out_pDecl, in_pA3);
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
	private:
		inline static FUNCTION_PTR(boost::shared_ptr<CPixelShaderData>&, __cdecl, ms_fpGetShaderFromPackfilePS, ASLR(0x00C2EC30), boost::shared_ptr<CPixelShaderData>&, hh::ut::PackFile&, const char*);
		inline static FUNCTION_PTR(boost::shared_ptr<CVertexShaderData>&, __cdecl, ms_fpGetShaderFromPackfileVS, ASLR(0x00C2E780), boost::shared_ptr<CVertexShaderData>&, hh::ut::PackFile&, const char*);

	public:
		inline static boost::shared_ptr<CPixelShaderData> GetShaderFromPackfilePS(ut::PackFile& in_rPac, const char* in_pName)
		{
			boost::shared_ptr<CPixelShaderData> ret{};
			ms_fpGetShaderFromPackfilePS(ret, in_rPac, in_pName);
			return ret;
		}

		inline static boost::shared_ptr<CVertexShaderData> GetShaderFromPackfileVS(ut::PackFile& in_rPac, const char* in_pName)
		{
			boost::shared_ptr<CVertexShaderData> ret{};
			ms_fpGetShaderFromPackfileVS(ret, in_rPac, in_pName);
			return ret;
		}
	};
}

namespace Extra::fx
{
	struct SShaderPair
	{
		boost::shared_ptr<hh::mr::CVertexShaderData> spVertexShader{};
		boost::shared_ptr<hh::mr::CPixelShaderData> spPixelShader{};
	};

	// Size 60
	struct STextureSurfacePair
	{
		hh::ut::ScopedComPtr<hh::rsdx::RsdxBaseTexture9> Textures[2]{};
		hh::ut::ScopedComPtr<hh::rsdx::RsdxSurface9> Surfaces[2]{};
		short Unk1{};
		short Levels{};
		short Width3{};
		short Height3{};
		uint Width2{};
		uint Height2{};
		uint Width{};
		uint Height{};
		
		hh::rsdx::_RsdxFormat Format{};
		INSERT_PADDING(12) {};
		const char* pName{};
	};

	struct SResourceContext
	{
		SShaderPair Shaders[83]{};
		STextureSurfacePair Textures[60]{};
	};

	inline static void GetShaderFromPackfile(SShaderPair& out_rPair, hh::ut::PackFile& in_rPac, const char* in_pVtxShaderName, const char* in_pPixelShaderName)
	{
		out_rPair.spVertexShader = hh::mr::GetMirageVertexShaderDataFromPackfile(in_rPac, in_pVtxShaderName);
		out_rPair.spPixelShader = hh::mr::GetMiragePixelShaderDataFromPackfile(in_rPac, in_pPixelShaderName);
	}

	inline static void GetShaderFromPackfile(SShaderPair& out_rPair, hh::ut::PackFile& in_rPac, const char* in_pShaderName)
	{
		out_rPair.spVertexShader = hh::mr::GetMirageVertexShaderDataFromPackfile(in_rPac, in_pShaderName);
		out_rPair.spPixelShader = hh::mr::GetMiragePixelShaderDataFromPackfile(in_rPac, in_pShaderName);
	}
}