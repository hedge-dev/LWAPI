#pragma once

namespace app::game
{
	class PhysicsQueryJob : public fnd::ReferencedObject
	{
	public:
		enum Type : char
		{
			eType_Raycast
		};

		csl::ut::Enum<Type, char> Type{};

		PhysicsQueryJob(Type in_type) : Type(in_type) {}
	};
}