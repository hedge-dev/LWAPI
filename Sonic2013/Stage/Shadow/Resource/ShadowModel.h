#pragma once

namespace app::res
{
	struct ResShadowModelData
	{
		
	};

	class ResShadowModel : public hh::ut::ResCommon<ResShadowModelData>
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FB6F0C));
		constexpr static hh::rsdx::_D3DVERTEXELEMENT9 ms_VtxLayout[5] = 
		{
			{ 0, 0x00, D3DDECLTYPE_FLOAT3 , D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION    , 0},
			{ 0, 0x0C, D3DDECLTYPE_FLOAT3 , D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL      , 0},
			{ 0, 0x18, D3DDECLTYPE_UBYTE4N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT , 0},
			{ 0, 0x1C, D3DDECLTYPE_UBYTE4 , D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0},
			D3DDECL_END()
		};

	public:
		hh::mr::CVertexDeclarationPtr m_VertexDecl{};

		ResShadowModel() : ResCommon<app::res::ResShadowModelData>(nullptr)
		{
			
		}

		ResShadowModel(void* in_pRes) : ResCommon<app::res::ResShadowModelData>(in_pRes)
		{
			gfx::RenderManager::GetInstance()->GetRenderingDevice()->CreateVertexDeclaration(ms_VtxLayout, &m_VertexDecl);
		}

		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};
}