#pragma once

namespace app::game
{
	class GravityEffect : public fnd::ReferencedObject
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00FD7C30));

		virtual const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const
		{
			return GetRuntimeTypeInfoStatic();
		}

		virtual void Init();
		virtual void GetDirection(csl::math::Vector3& in_rVec, csl::math::Vector3* out_pVec) const;
		virtual void ApplyEffect();
	};
}
