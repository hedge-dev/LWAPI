#pragma once

namespace hh::gfx::res
{
	struct ResTextureData
	{
		IDirect3DTexture9* pTexture{};
		uint ArraySize{};
		size_t DataSize{};
		ResNameData Name{};
		void* pData{};
		INSERT_PADDING(20) {};
		csl::fnd::IAllocator* pAllocator{};
		ResNameData AllocatorName{};

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