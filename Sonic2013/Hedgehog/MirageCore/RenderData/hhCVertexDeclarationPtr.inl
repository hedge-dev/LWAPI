#include "hhVertexDeclarationPtr.h"
#pragma once

namespace hh::mr
{
	inline CVertexDeclarationPtr::CVertexDeclarationPtr(const CVertexDeclarationPtr& in_other)
	{
		m_pDecl = in_other.m_pDecl;
		m_pInfrastructure = in_other.m_pInfrastructure;

		if (m_pInfrastructure)
			m_pInfrastructure->AddRefVertexDeclaration(&m_pDecl);
	}

	inline hh::mr::CVertexDeclarationPtr::~CVertexDeclarationPtr()
	{
		if (!m_pInfrastructure)
			return;

		m_pInfrastructure->ReleaseVertexDeclaration(&m_pDecl);
		m_pInfrastructure = nullptr;
	}

	inline CVertexDeclarationPtr& CVertexDeclarationPtr::operator=(const CVertexDeclarationPtr& in_other)
	{
		if (m_pInfrastructure)
		{
			m_pInfrastructure->ReleaseVertexDeclaration(&m_pDecl);
			m_pInfrastructure = nullptr;
		}

		m_pDecl = in_other.m_pDecl;
		m_pInfrastructure = in_other.m_pInfrastructure;

		if (m_pInfrastructure)
			m_pInfrastructure->AddRefVertexDeclaration(&m_pDecl);

		return *this;
	}
}