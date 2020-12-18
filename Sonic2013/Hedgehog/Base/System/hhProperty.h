#pragma once

namespace app::fnd
{
	class Property
	{
	private:
		unsigned int propertyID{};
		unsigned int value{};
		unsigned int unk1{};
		unsigned int unk2{};

	public:
		Property(unsigned int id) : propertyID(id) {}

		Property(unsigned int id, unsigned int value_) : propertyID(id), value(value_) {}

		Property(unsigned int id, unsigned int value_, unsigned int a3) : propertyID(id), value(value_), unk1(a3) {}
	};
}
