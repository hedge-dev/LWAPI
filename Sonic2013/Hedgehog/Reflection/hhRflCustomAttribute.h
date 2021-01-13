#pragma once

namespace app::fnd
{
	class RflClass;

	class RflCustomAttribute
	{
	protected:
		const char* p_name{};
		const void* p_data{};
		RflClass* p_type{};

	public:
		[[nodiscard]] const char* GetName() const
		{
			return p_name;
		}

		[[nodiscard]] const void* GetData() const
		{
			return p_data;
		}

		[[nodiscard]] const RflClass* GetType() const
		{
			return p_type;
		}
	};
	
	class RflCustomAttributes
	{
	protected:
		const RflCustomAttribute* p_attributes{};
		const size_t m_count{};

	public:
		[[nodiscard]] const RflCustomAttribute* GetAttribute(const char* name) const
		{
			for (size_t i = 0; i < m_count; i++)
			{
				const auto* attribute = &p_attributes[i];

				if (attribute->GetName() == name || !strcmp(attribute->GetName(), name))
				{
					return attribute;
				}
			}
			
			return nullptr;
		}
	};
}