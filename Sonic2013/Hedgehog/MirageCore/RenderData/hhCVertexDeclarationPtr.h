#pragma once

namespace hh::mr
{
	class CRenderingInfrastructure;
	class CVertexDeclarationPtr : public hh::base::CObject
	{
	public:
		rsdx::RsdxVertexDeclaration9* pDecl{};
		CRenderingInfrastructure* pInfrastructure{};

		CVertexDeclarationPtr()
		{
			
		}

		CVertexDeclarationPtr(const CVertexDeclarationPtr& in_rOther);
		~CVertexDeclarationPtr();

		operator rsdx::RsdxVertexDeclaration9*() const
		{
			return pDecl;
		}

		CVertexDeclarationPtr& operator=(const CVertexDeclarationPtr& in_rOther);
	};
}
