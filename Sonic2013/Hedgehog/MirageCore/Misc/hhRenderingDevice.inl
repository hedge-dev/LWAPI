#pragma once

namespace hh::mr
{
	inline void CRenderingDevice::SetVertexDeclaration(IDirect3DVertexDeclaration9* in_pDecl)
	{
		if (m_pCurrentVertexDecl == in_pDecl)
			return;

		if (!m_LockVertexDecl)
			m_pCurrentVertexDecl = in_pDecl;

		m_pD3DDevice->SetVertexDeclaration(in_pDecl);
	}

	inline void CRenderingDevice::SetShader(const Extra::fx::SShaderPair& in_pair)
	{
		SetShader(in_pair.m_spVertexShader, in_pair.m_spPixelShader);
	}

	inline void CRenderingDevice::SetShaderFromPool(ShaderType in_type)
	{
		m_pRenderingInfrastructure->SetShaderFromPool(this, in_type);
	}

	inline void CRenderingDevice::SetPixelShaderParameterF(const base::CStringSymbol& in_name, const float* in_pData,
		uint in_offset, uint in_count, CPixelShaderData* in_pShader)
	{
		ms_fpSetPixelShaderParameterF(this, in_name, in_pData, in_offset, in_count, in_pShader);
	}

	inline void CRenderingDevice::SetVertexShaderParameterF(const base::CStringSymbol& in_name, const float* in_pData, 
		uint in_offset, uint in_count, CVertexShaderData* in_pShader)
	{
		ms_fpSetVertexShaderParameterF(this, in_name, in_pData, in_offset, in_count, in_pShader);
	}
}