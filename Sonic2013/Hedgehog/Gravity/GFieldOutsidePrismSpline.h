#pragma once

namespace app::game
{
	class GFieldOutsidePrismSpline : public GFieldCylinderSpline
	{
	public:
		float Radius{ 1.0f };
		int Unk2{};

		DEFINE_RTTI_PTR(ASLR(0x00F6C304));

		GFieldOutsidePrismSpline() : GFieldCylinderSpline(game::GravityType::eGravityType_OutsidePrismSpline)
		{

		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}
	};
}
