#pragma once

namespace app::fnd
{
	class RflTypeInfo
	{
	public:
		typedef void* TypeConstructor(void* pInstance, csl::fnd::IAllocator* pAllocator);
		typedef void TypeFinisher(void* pInstance);
		typedef void TypeCleaner(void* pInstance);
		
	protected:
		const char* m_pName;
		const char* m_pScopedName; // Assuming they're copying havok
		TypeConstructor* m_fpConstruct;
		TypeFinisher* m_fpFinisher;
		TypeCleaner* m_fpCleaner;
		size_t m_Size;

	public:
		const char* GetName() const
		{
			return m_pName;
		}

		const char* GetScopedName() const
		{
			return m_pScopedName;
		}

		void ConstructObject(void* pInst, csl::fnd::IAllocator* pAllocator) const
		{
			if (!m_fpConstruct)
				return;

			m_fpConstruct(pInst, pAllocator);
		}

		void FinishLoadedObject(void* pInstance) const
		{
			if (m_fpFinisher)
				m_fpFinisher(pInstance);
		}

		void CleanupLoadedObject(void* pInstance) const
		{
			if (m_fpCleaner)
				m_fpCleaner(pInstance);
		}

		size_t GetSize() const
		{
			return m_Size;
		}
	};
}