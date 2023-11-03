#pragma once

namespace app::fnd
{
	class GameServiceClass
	{
		const char* m_pName;
		initializeService* m_pInitializer;
		RflClass* m_pClass;

	public:
		GameServiceClass(const char* pName, initializeService& rInitializer, RflClass* pClass = nullptr) : m_pName(pName),
			m_pInitializer(&rInitializer), m_pClass(pClass)
		{
			
		}

		[[nodiscard]] const char* GetName() const
		{
			return m_pName;
		}

		[[nodiscard]] GameService* Construct(csl::fnd::IAllocator* allocator) const;
	};
}