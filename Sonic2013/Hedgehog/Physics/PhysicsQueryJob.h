#pragma once

namespace app::game
{
	class PhysicsQueryJob : public fnd::ReferencedObject
	{
	public:
		enum Type : char
		{
			Type_Raycast
		};

		csl::ut::Enum<Type, char> m_Type{};

		PhysicsQueryJob(Type in_type) : m_Type(in_type) {}
	};
}