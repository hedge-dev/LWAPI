#pragma once

namespace app::fnd
{
	class RflClass;

	class RflCustomAttribute
	{
	protected:
		const char* m_pName{};
		const void* m_pData{};
		RflClass* m_pType{};

	public:
		[[nodiscard]] const char* GetName() const
		{
			return m_pName;
		}

		[[nodiscard]] const void* GetData() const
		{
			return m_pData;
		}

		[[nodiscard]] const RflClass* GetType() const
		{
			return m_pType;
		}
	};
	
	class RflCustomAttributes
	{
	protected:
		const RflCustomAttribute* m_pAttributes{};
		const size_t m_Count{};

	public:
		[[nodiscard]] const RflCustomAttribute* GetAttribute(const char* name) const
		{
			for (size_t i = 0; i < m_Count; i++)
			{
				const auto* attribute = &m_pAttributes[i];

				if (attribute->GetName() == name || !strcmp(attribute->GetName(), name))
				{
					return attribute;
				}
			}
			
			return nullptr;
		}
	};
}