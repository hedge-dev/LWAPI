#pragma once

namespace hh::ut
{
	class ResourceTypeInfo;
	
	class PackFile : public hh::ut::ResCommon<PackFileHeaderDataTag>
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsValidHeader, ASLR(0x00C1A770), const PackFile*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpBind, ASLR(0x00C18DF0), PackFile*, csl::fnd::IAllocator*, PackFile);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpGetResource, ASLR(0x00C191E0), PackFile*, const ResourceTypeInfo&, const char*, uint*);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpGetResourceByIndex, ASLR(0x00C19230), PackFile*, const ResourceTypeInfo&, size_t, uint*);
		inline static FUNCTION_PTR(size_t, __thiscall, ms_fpGetResourceCount, ASLR(0x00C192C0), const PackFile*, const ResourceTypeInfo&);
		inline static FUNCTION_PTR(const char*, __thiscall, ms_fpGetResourceIDName, ASLR(0x00C19280), const PackFile*, const ResourceTypeInfo&, size_t);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCleanup, ASLR(0x00C19090), PackFile*);
		
	public:
		bool IsValidHeader() const
		{
			return ms_fpIsValidHeader(this);
		}
		
		PackFile(void* in_pData) : ResCommon<PackFileHeaderDataTag>(static_cast<PackFileHeaderDataTag*>(in_pData))
		{
			if (IsValidHeader())
			{
				m_pRes->ConvertEndian();
			}
		}

		PackFile(PackFile& pack) : ResCommon<PackFileHeaderDataTag>(pack.m_pRes)
		{
			
		}

		void Bind(csl::fnd::IAllocator* in_pAllocator, PackFile in_other)
		{
			ms_fpBind(this, in_pAllocator, in_other);
		}

		void* GetResource(const ResourceTypeInfo& in_rInfo, const char* in_pName, uint* in_pA3)
		{
			return ms_fpGetResource(this, in_rInfo, in_pName, in_pA3);
		}

		void* GetResource(const ResourceTypeInfo& in_rInfo, size_t in_index, uint* in_pA3)
		{
			return ms_fpGetResourceByIndex(this, in_rInfo, in_index, in_pA3);
		}

		size_t GetResourceCount(const ResourceTypeInfo& in_rInfo) const
		{
			return ms_fpGetResourceCount(this, in_rInfo);
		}

		const char* GetResourceIDName(const ResourceTypeInfo& in_rInfo, size_t in_index) const
		{
			return ms_fpGetResourceIDName(this, in_rInfo, in_index);
		}
		
		template<typename T>
		T Get(const char* in_pName, uint* in_pA2 = nullptr)
		{
			return T{ GetResource(T::staticTypeInfo(), in_pName, in_pA2) };
		}

		template<typename T>
		T Get(size_t in_index, uint* in_pA2 = nullptr)
		{
			return T{ GetResource(T::staticTypeInfo(), in_index, in_pA2) };
		}

		template<typename T>
		size_t GetCount() const
		{
			return GetResourceCount(T::staticTypeInfo());
		}

		template<typename T>
		const char* GetIDName(size_t in_index) const
		{
			return GetResourceIDName(T::staticTypeInfo(), in_index);
		}

		void Cleanup()
		{
			ms_fpCleanup(this);
		}
	};
}
