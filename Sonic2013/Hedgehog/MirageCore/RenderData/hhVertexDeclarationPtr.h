#pragma once

namespace hh::mr
{
	class CRenderingInfrastructure;
	class CVertexDeclarationPtr : public hh::base::CObject
	{
	public:
		rsdx::RsdxVertexDeclaration9* m_pDecl{};
		CRenderingInfrastructure* m_pInfrastructure{};

		CVertexDeclarationPtr()
		{
			
		}

		CVertexDeclarationPtr(const CVertexDeclarationPtr& in_other);
		~CVertexDeclarationPtr();

		operator rsdx::RsdxVertexDeclaration9*() const
		{
			return m_pDecl;
		}

		CVertexDeclarationPtr& operator=(const CVertexDeclarationPtr& in_other);
	};
}
