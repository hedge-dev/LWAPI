#pragma once

namespace app::game
{
	class GFieldSvSpline : public GravityField
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00F6C358));

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		fnd::Handle<PathComponent> Path{};
		csl::math::Vector3 Unk1{ 10.0f, 10.0f, 0.0f };
		float Unk2{ 100.0f };

		PathComponent* GetPath() const
		{
			return Path.Get();
		}
	};
}
