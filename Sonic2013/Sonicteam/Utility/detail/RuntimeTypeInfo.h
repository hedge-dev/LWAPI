#pragma once

namespace csl::ut
{
	namespace detail 
	{
		class RuntimeTypeInfo
		{
			// This is as far as my knowledge goes.
			// Apparent, this is just as far as it goes.
		protected:
			const RuntimeTypeInfo* m_pBaseType{};

		public:
			RuntimeTypeInfo(const RuntimeTypeInfo* pBase) : m_pBaseType(pBase)
			{

			}

			bool IsDerivedFrom(const RuntimeTypeInfo* pInfo) const
			{
				if (!this)
					return false;

				const RuntimeTypeInfo* pBase = this;
				while (pBase != pInfo)
				{
					pBase = pBase->m_pBaseType;
					if (!pBase)
						return false;
				}

				return true;
			}
		};
	}

	template<typename DstType, typename SrcType>
	inline static DstType* DynamicCast(SrcType* pSrc) 
	{
		if (!pSrc)
			return nullptr;

		if (DstType::GetRuntimeTypeInfoStatic()->IsDerivedFrom(pSrc->GetRuntimeTypeInfo()))
		{
			return reinterpret_cast<DstType*>(pSrc);
		}

		return nullptr;
	}
}

#define DEFINE_RTTI_BASE(BASE) inline static const csl::ut::detail::RuntimeTypeInfo ms_RTTI{BASE::GetRuntimeTypeInfoStatic()}; \
static const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfoStatic() { return &ms_RTTI; }

#define DEFINE_RTTI inline static const csl::ut::detail::RuntimeTypeInfo ms_RTTI{nullptr}; \
static const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfoStatic() { return &ms_RTTI; }

#define DEFINE_RTTI_GETTER const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() { return GetRuntimeTypeInfoStatic(); }

#define DEFINE_RTTI_PTR(ADDRESS) inline static const csl::ut::detail::RuntimeTypeInfo* ms_pRTTI = (const csl::ut::detail::RuntimeTypeInfo*)(ADDRESS); \
inline static const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfoStatic() { return ms_pRTTI; }