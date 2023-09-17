#pragma once

namespace app::game
{
	class GFieldInsidePrismSpline : public GFieldCylinderSpline
	{
	public:
		float Radius{ 1.0f };
		int Unk2{};

		DEFINE_RTTI_PTR(ASLR(0x00F6C298));

		GFieldInsidePrismSpline() : GFieldCylinderSpline(game::GravityType::eGravityType_InsidePrismSpline)
		{

		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}
	};
}
