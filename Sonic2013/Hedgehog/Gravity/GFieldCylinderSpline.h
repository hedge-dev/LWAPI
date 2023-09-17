#pragma once

namespace app::game
{
	class GFieldCylinderSpline : public GravityField
	{
	public:
		float Unk1{};
		fnd::Handle<game::PathComponent> Path{};

		DEFINE_RTTI_PTR(ASLR(0x00F6C1DC));

		GFieldCylinderSpline(game::GravityType in_type) : GravityField(in_type)
		{

		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		PathComponent* GetPath()
		{
			return Path.Get();
		}
	};
}
