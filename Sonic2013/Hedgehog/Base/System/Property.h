#pragma once

namespace app::fnd
{
	class PropertyValue
	{
	private:
		unsigned int propertyID{};
		unsigned int value{};
		unsigned int unk1{};
		unsigned int unk2{};

	public:
		PropertyValue(unsigned int id) : propertyID(id) {}

		PropertyValue(unsigned int id, unsigned int value_) : propertyID(id), value(value_) {}

		PropertyValue(unsigned int id, unsigned int value_, unsigned int a3) : propertyID(id), value(value_), unk1(a3) {}
	};
}
