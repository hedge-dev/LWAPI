#pragma once
struct IDirect3DDevice9;

namespace Extra::fx
{
	struct SShaderPair;
}

namespace hh::rsdx
{
	typedef D3DRENDERSTATETYPE _D3DRENDERSTATETYPE;
	typedef csl::math::Vector4 rsdx_simd_float4;
}

namespace hh::mr
{
	class CPixelShaderData;
	class CVertexShaderData;
	enum ShaderType
	{
		ShaderType_Default, ShaderType_Error, ShaderType_FilterT, ShaderType_CopyColor
	};

	class CRenderingInfrastructure;

	// 3588
	class CRenderingDevice : public base::CObject
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetShaderFromPool, ASLR(0x00C2F9E0), CRenderingDevice*, ShaderType);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetShader, ASLR(0x00488580), CRenderingDevice*, const boost::shared_ptr<CVertexShaderData>&, const boost::shared_ptr<CPixelShaderData>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetCullMode, ASLR(0x00907D40), CRenderingDevice*, uint);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLockRenderState, ASLR(0x00C2FC50), CRenderingDevice*, rsdx::_D3DRENDERSTATETYPE);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUnlockRenderState, ASLR(0x00C2FC70), CRenderingDevice*, rsdx::_D3DRENDERSTATETYPE);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPushRenderState, ASLR(0x00C2FE10), CRenderingDevice*, rsdx::_D3DRENDERSTATETYPE, uint);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPopRenderState, ASLR(0x00C2FE80), CRenderingDevice*, rsdx::_D3DRENDERSTATETYPE);

		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLightFieldData, ASLR(0x00C32070), CRenderingDevice*, const rsdx::rsdx_simd_float4*, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetPixelShaderParameterF, ASLR(0x004892A0), CRenderingDevice*, const base::CStringSymbol&, const float*, uint offset, uint count, CPixelShaderData*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetVertexShaderParameterF, ASLR(0x00488820), CRenderingDevice*, const base::CStringSymbol&, const float*, uint offset, uint count, CVertexShaderData*);

		CRenderingInfrastructure* m_pRenderingInfrastructure;
		IDirect3DDevice9* m_pD3DDevice;
		INSERT_PADDING(2788);
		IDirect3DVertexDeclaration9* m_pCurrentVertexDecl;
		INSERT_PADDING(8);
		CVertexShaderData* m_pCurrentVertexShaderData;
		CPixelShaderData* m_pCurrentPixelShaderData;
		INSERT_PADDING(639);
		bool m_LockVertexDecl;
		INSERT_PADDING(132);

		CRenderingDevice()
		{
			ASSERT_OFFSETOF(CRenderingDevice, m_pCurrentVertexDecl, 2796);
			ASSERT_OFFSETOF(CRenderingDevice, m_pCurrentVertexShaderData, 2808);
			ASSERT_OFFSETOF(CRenderingDevice, m_pCurrentPixelShaderData, 2812);
			ASSERT_OFFSETOF(CRenderingDevice, m_LockVertexDecl, 3455);
		}

		void SetVertexDeclaration(IDirect3DVertexDeclaration9* in_pDecl);
		void SetPixelShaderParameterF(const base::CStringSymbol& in_name, const float* in_pData, uint in_offset, uint in_count, CPixelShaderData* in_pShader);
		void SetVertexShaderParameterF(const base::CStringSymbol& in_name, const float* in_pData, uint in_offset, uint in_count, CVertexShaderData* in_pShader);
		void SetShaderFromPool(ShaderType in_type);
		void SetShader(const Extra::fx::SShaderPair& in_pair);
		void SetShader(const boost::shared_ptr<CVertexShaderData>& in_vertexShader, const boost::shared_ptr<CPixelShaderData>& in_pixelShader)
		{
			ms_fpSetShader(this, in_vertexShader, in_pixelShader);
		}

		void SetCullMode(uint in_mode)
		{
			ms_fpSetCullMode(this, in_mode);
		}

		void PushRenderState(rsdx::_D3DRENDERSTATETYPE in_type, uint state)
		{
			ms_fpPushRenderState(this, in_type, state);
		}

		void PopRenderState(rsdx::_D3DRENDERSTATETYPE in_type)
		{
			ms_fpPopRenderState(this, in_type);
		}

		void LockRenderState(rsdx::_D3DRENDERSTATETYPE in_type)
		{
			ms_fpLockRenderState(this, in_type);
		}

		void UnlockRenderState(rsdx::_D3DRENDERSTATETYPE in_type)
		{
			ms_fpUnlockRenderState(this, in_type);
		}

		void SetLightFieldData(const rsdx::rsdx_simd_float4* in_pData, bool in_a2)
		{
			ms_fpSetLightFieldData(this, in_pData, in_a2);
		}

		template<typename T>
		void SetVertexShaderParameter(const base::CStringSymbol& in_name, const T& in_data, uint in_offset, uint in_count, CVertexShaderData* in_pShader)
		{
			SetVertexShaderParameterF(in_name, reinterpret_cast<const float*>(&in_data), in_offset * sizeof(T), (sizeof(T) / sizeof(float)) * in_count, in_pShader);
		}

		template<typename T>
		void SetPixelShaderParameter(const base::CStringSymbol& in_name, const T& in_data, uint in_offset, uint in_count, CPixelShaderData* in_pShader)
		{
			SetPixelShaderParameterF(in_name, reinterpret_cast<const float*>(&in_data), in_offset * sizeof(T), (sizeof(T) / sizeof(float)) * in_count, in_pShader);
		}

		template<typename T>
		void SetPixelShaderParameter(const base::CStringSymbol& in_name, const T& in_data)
		{
			SetPixelShaderParameter(in_name, in_data, 0, 1, m_pCurrentPixelShaderData);
		}

		template<typename T>
		void SetVertexShaderParameter(const base::CStringSymbol& in_name, const T& in_data)
		{
			SetVertexShaderParameter(in_name, in_data, 0, 1, m_pCurrentVertexShaderData);
		}
	};
}