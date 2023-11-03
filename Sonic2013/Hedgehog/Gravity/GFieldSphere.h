#pragma once

namespace app::game
{
	class GFieldSphere : public GravityField
	{
	public:
		float Radius{};
		float Unk2{};

		DEFINE_RTTI_PTR(ASLR(0x00F6C32C));

		GFieldSphere() : GravityField(game::GravityType::eGravityType_Sphere)
		{

		}

		csl::math::Vector3 GetPosition() const
		{
			return pTransform->Frame.Unk3.GetTranslation();
		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}
	};
}
