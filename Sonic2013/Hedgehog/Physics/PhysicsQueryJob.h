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

		csl::ut::Enum<Type, char> QueryType{};

		PhysicsQueryJob(Type in_type) : QueryType(in_type) {}
	};
}