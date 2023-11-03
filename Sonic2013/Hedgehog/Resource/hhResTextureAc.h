#pragma once

namespace hh::gfx::res
{
	struct ResTextureData
	{
		IDirect3DTexture9* m_pTexture{};
		uint m_ArraySize{};
		size_t m_DataSize{};
		ResNameData m_Name{};
		void* m_pData{};
		INSERT_PADDING(20) {};
		csl::fnd::IAllocator* m_pAllocator{};
		ResNameData m_AllocatorName{};

		ResTextureData()
		{

		}
	};

	class ResTexture : public ut::ResCommon<ResTextureData>
	{
		inline static ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<ut::ResourceTypeInfo*>(ASLR(0x00FCE64C));

	public:
		static const ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};
}