#pragma once

namespace app::fnd
{
	class GameServiceClass
	{
		const char* m_pName;
		initializeService* m_pInitializer;
		RflClass* m_pClass;

	public:
		GameServiceClass(const char* in_pName, initializeService& in_rInitializer, RflClass* in_pClass = nullptr) : m_pName(in_pName),
			m_pInitializer(&in_rInitializer), m_pClass(in_pClass)
		{
			
		}

		[[nodiscard]] const char* GetName() const
		{
			return m_pName;
		}

		[[nodiscard]] GameService* Construct(csl::fnd::IAllocator* in_pAllocator) const;
	};
}