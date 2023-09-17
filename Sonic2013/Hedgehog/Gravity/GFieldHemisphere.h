#pragma once

namespace app::game
{
	class GFieldHemisphere : public GravityField
	{
	public:
		float Radius{};
		float Unk2{};
		int Unk3{};

		DEFINE_RTTI_PTR(ASLR(0x00FD7C04));

		GFieldHemisphere() : GravityField(game::GravityType::eGravityType_Hemisphere)
		{

		}

		csl::math::Vector3 GetPosition() const
		{
			return pTransform->m_Frame.m_Unk3.GetTranslation();
		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}
	};
}
