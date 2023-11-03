#pragma once
struct IDirect3DDevice9;

namespace Extra::fx
{
	struct SShaderPair;
}

namespace hh::mr
{
	class CPixelShaderData;
	class CVertexShaderData;
	enum ShaderType
	{
		eShaderType_Default, eShaderType_Error, eShaderType_FilterT, eShaderType_CopyColor
	};

	class CRenderingInfrastructure;

	// 3588
	class CRenderingDevice : public base::CObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetShaderFromPool, ASLR(0x00C2F9E0), CRenderingDevice*, ShaderType);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetShader, ASLR(0x00488580), CRenderingDevice*, const boost::shared_ptr<CVertexShaderData>&, const boost::shared_ptr<CPixelShaderData>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetCullMode, ASLR(0x00907D40), CRenderingDevice*, uint);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLockRenderState, ASLR(0x00C2FC50), CRenderingDevice*, rsdx::_D3DRENDERSTATETYPE);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUnlockRenderState, ASLR(0x00C2FC70), CRenderingDevice*, rsdx::_D3DRENDERSTATETYPE);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPushRenderState, ASLR(0x00C2FE10), CRenderingDevice*, rsdx::_D3DRENDERSTATETYPE, uint);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPopRenderState, ASLR(0x00C2FE80), CRenderingDevice*, rsdx::_D3DRENDERSTATETYPE);

		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLightFieldData, ASLR(0x00C32070), CRenderingDevice*, const rsdx::rsdx_simd_float4*, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetHasBone, ASLR(0x00488610), CRenderingDevice*, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetPixelShaderParameterF, ASLR(0x004892A0), CRenderingDevice*, const base::CStringSymbol&, const float*, uint offset, uint count, CPixelShaderData*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetVertexShaderParameterF, ASLR(0x00488820), CRenderingDevice*, const base::CStringSymbol&, const float*, uint offset, uint count, CVertexShaderData*);

	public:
		CRenderingInfrastructure* pRenderingInfrastructure;
		hh::rsdx::RsdxDevice* pD3DDevice;
		INSERT_PADDING(2788);
		rsdx::RsdxVertexDeclaration9* pCurrentVertexDecl;
		INSERT_PADDING(8);
		CVertexShaderData* pCurrentVertexShaderData;
		CPixelShaderData* pCurrentPixelShaderData;
		INSERT_PADDING(639);
		bool LockVertexDecl;
		INSERT_PADDING(132);

		CRenderingDevice()
		{
			ASSERT_OFFSETOF(CRenderingDevice, pCurrentVertexDecl, 2796);
			ASSERT_OFFSETOF(CRenderingDevice, pCurrentVertexShaderData, 2808);
			ASSERT_OFFSETOF(CRenderingDevice, pCurrentPixelShaderData, 2812);
			ASSERT_OFFSETOF(CRenderingDevice, LockVertexDecl, 3455);
		}

		void SetVertexDeclaration(rsdx::RsdxVertexDeclaration9* in_pDecl);
		void SetPixelShaderParameterF(const base::CStringSymbol& in_rName, const float* in_pData, uint in_offset, uint in_count, CPixelShaderData* in_pShader);
		void SetVertexShaderParameterF(const base::CStringSymbol& in_rName, const float* in_pData, uint in_offset, uint in_count, CVertexShaderData* in_pShader);
		void SetShaderFromPool(ShaderType in_type);
		void SetShader(const Extra::fx::SShaderPair& in_rPair);
		void SetShader(const boost::shared_ptr<CVertexShaderData>& in_rVertexShader, const boost::shared_ptr<CPixelShaderData>& in_rPixelShader)
		{
			ms_fpSetShader(this, in_rVertexShader, in_rPixelShader);
		}

		void SetHasBone(bool in_value)
		{
			ms_fpSetHasBone(this, in_value);
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
		void SetVertexShaderParameter(const base::CStringSymbol& in_rName, const T& in_rData, uint in_offset, uint in_count, CVertexShaderData* in_pShader)
		{
			SetVertexShaderParameterF(in_rName, reinterpret_cast<const float*>(&in_rData), in_offset * sizeof(T), (sizeof(T) / sizeof(float)) * in_count, in_pShader);
		}

		template<typename T>
		void SetPixelShaderParameter(const base::CStringSymbol& in_rName, const T& in_rData, uint in_offset, uint in_count, CPixelShaderData* in_pShader)
		{
			SetPixelShaderParameterF(in_rName, reinterpret_cast<const float*>(&in_rData), in_offset * sizeof(T), (sizeof(T) / sizeof(float)) * in_count, in_pShader);
		}

		template<typename T>
		void SetPixelShaderParameter(const base::CStringSymbol& in_rName, const T& in_rData)
		{
			SetPixelShaderParameter(in_rName, in_rData, 0, 1, m_pCurrentPixelShaderData);
		}

		template<typename T>
		void SetVertexShaderParameter(const base::CStringSymbol& in_rName, const T& in_rData)
		{
			SetVertexShaderParameter(in_rName, in_rData, 0, 1, m_pCurrentVertexShaderData);
		}
	};
}