#include "hhVertexDeclarationPtr.h"
#pragma once

namespace hh::mr
{
	inline CVertexDeclarationPtr::CVertexDeclarationPtr(const CVertexDeclarationPtr& in_rOther)
	{
		pDecl = in_rOther.m_pDecl;
		pInfrastructure = in_rOther.m_pInfrastructure;

		if (pInfrastructure)
			pInfrastructure->AddRefVertexDeclaration(&pDecl);
	}

	inline hh::mr::CVertexDeclarationPtr::~CVertexDeclarationPtr()
	{
		if (!pInfrastructure)
			return;

		pInfrastructure->ReleaseVertexDeclaration(&pDecl);
		pInfrastructure = nullptr;
	}

	inline CVertexDeclarationPtr& CVertexDeclarationPtr::operator=(const CVertexDeclarationPtr& in_rOther)
	{
		if (pInfrastructure)
		{
			pInfrastructure->ReleaseVertexDeclaration(&pDecl);
			pInfrastructure = nullptr;
		}

		pDecl = in_rOther.pDecl;
		pInfrastructure = in_rOther.pInfrastructure;

		if (pInfrastructure)
			pInfrastructure->AddRefVertexDeclaration(&pDecl);

		return *this;
	}
}