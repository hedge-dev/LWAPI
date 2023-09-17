#pragma once

namespace app::game
{
	class GFieldOutsideCylinderSpline : public GFieldCylinderSpline
	{
	public:
		float Radius{ 1.0f };

		DEFINE_RTTI_PTR(ASLR(0x00F6C2D0));

		GFieldOutsideCylinderSpline() : GFieldCylinderSpline(game::GravityType::eGravityType_OutsideCylinderSpline)
		{

		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}
	};
}
