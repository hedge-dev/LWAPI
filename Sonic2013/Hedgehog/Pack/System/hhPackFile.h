#pragma once

namespace hh::ut
{
	class ResourceTypeInfo;
	
	class PackFile : public app::fnd::ResCommon<PackFileHeaderDataTag>
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsValidHeader, ASLR(0x00C1A770), const PackFile*);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpGetResource, ASLR(0x00C191E0), PackFile*, const ResourceTypeInfo&, const char*, uint*);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpGetResourceByIndex, ASLR(0x00C19230), PackFile*, const ResourceTypeInfo&, size_t, uint*);
		inline static FUNCTION_PTR(size_t, __thiscall, ms_fpGetResourceCount, ASLR(0x00C192C0), const PackFile*, const ResourceTypeInfo&);
		
	public:
		bool IsValidHeader() const
		{
			return ms_fpIsValidHeader(this);
		}
		
		PackFile(void* pData) : ResCommon<PackFileHeaderDataTag>(static_cast<PackFileHeaderDataTag*>(pData))
		{
			if (IsValidHeader())
			{
				m_pRes->ConvertEndian();
			}
		}

		PackFile(PackFile& pack) : ResCommon<PackFileHeaderDataTag>(pack.m_pRes)
		{
			
		}

		void* GetResource(const ResourceTypeInfo& info, const char* pName, uint* a3)
		{
			return ms_fpGetResource(this, info, pName, a3);
		}

		void* GetResource(const ResourceTypeInfo& info, size_t index, uint* a3)
		{
			return ms_fpGetResourceByIndex(this, info, index, a3);
		}

		size_t GetResourceCount(const ResourceTypeInfo& info) const
		{
			return ms_fpGetResourceCount(this, info);
		}

		template<typename T>
		T* Get(const char* pName, uint* a2)
		{
			return static_cast<T*>(GetResource(T::staticTypeInfo(), pName, a2));
		}

		template<typename T>
		T* Get(size_t index, uint* a2)
		{
			return static_cast<T*>(GetResource(T::staticTypeInfo(), index, a2));
		}

		template<typename T>
		size_t GetCount()
		{
			return GetResourceCount(T::staticTypeInfo());
		}
	};
}
