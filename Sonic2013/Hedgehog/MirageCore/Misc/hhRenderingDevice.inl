#pragma once

namespace hh::mr
{
	inline void CRenderingDevice::SetVertexDeclaration(rsdx::RsdxVertexDeclaration9* in_pDecl)
	{
		if (pCurrentVertexDecl == in_pDecl)
			return;

		if (!LockVertexDecl)
			pCurrentVertexDecl = in_pDecl;

		pD3DDevice->SetVertexDeclaration(in_pDecl);
	}

	inline void CRenderingDevice::SetShader(const Extra::fx::SShaderPair& in_rPair)
	{
		SetShader(in_rPair.spVertexShader, in_pair.spPixelShader);
	}

	inline void CRenderingDevice::SetShaderFromPool(ShaderType in_type)
	{
		pRenderingInfrastructure->SetShaderFromPool(this, in_type);
	}

	inline void CRenderingDevice::SetPixelShaderParameterF(const base::CStringSymbol& in_rName, const float* in_pData,
		uint in_offset, uint in_count, CPixelShaderData* in_pShader)
	{
		ms_fpSetPixelShaderParameterF(this, in_rName, in_pData, in_offset, in_count, in_pShader);
	}

	inline void CRenderingDevice::SetVertexShaderParameterF(const base::CStringSymbol& in_rName, const float* in_pData, 
		uint in_offset, uint in_count, CVertexShaderData* in_pShader)
	{
		ms_fpSetVertexShaderParameterF(this, in_rName, in_pData, in_offset, in_count, in_pShader);
	}
}