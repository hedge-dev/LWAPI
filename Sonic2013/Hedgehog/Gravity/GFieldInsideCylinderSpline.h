#pragma once

namespace app::game
{
	class GFieldInsideCylinderSpline : public GFieldCylinderSpline
	{
	public:
		float Radius{ 1.0f };

		DEFINE_RTTI_PTR(ASLR(0x00F6C264));

		GFieldInsideCylinderSpline() : GFieldCylinderSpline(game::GravityType::eGravityType_InsideCylinderSpline)
		{

		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}
	};
}
