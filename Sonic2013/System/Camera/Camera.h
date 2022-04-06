#pragma once

namespace app::Camera
{
	typedef int EInterpolateType;

	class CCameraController;
	class CCamera : public GameObject
	{
		struct SCameraListUnit
		{
			CCameraController* m_pController{};
			EInterpolateType m_Interpolation{};
		};
	public:
		struct SCinfo
		{
			uint m_Unk1{};
			uint m_Viewport{};
			float m_NearClipPlane{ 1 };
			float m_FarClipPlane{ 10000 };
			float m_Fov{ 45 };
			uint m_Unk2{};
			uint m_Flags{ static_cast<uint>(-1)};
			uint m_Unk3{};
		};

		csl::ut::MoveArray<SCameraListUnit> m_Units{ GetAllocator() };
		INSERT_PADDING(384) {};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpCt, ASLR(0x00418920), CCamera*, const SCinfo&);

		CCamera(const SCinfo& in_info) : GameObject(true)
		{
			ms_fpCt(this, in_info);
		}
	};
}