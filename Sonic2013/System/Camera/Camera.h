#pragma once

namespace app::Camera
{
	typedef int EInterpolateType;

	class CCameraController;
	
	class CCamera : public GameObject
	{
		struct SCameraListUnit
		{
			CCameraController* pController{};
			EInterpolateType Interpolation{};
		};

	public:
		struct SCinfo
		{
			uint Unk1{};
			uint Viewport{};
			float NearClipPlane{ 1 };
			float FarClipPlane{ 10000 };
			float Fov{ 45 };
			uint Unk2{};
			uint Flags{ static_cast<uint>(-1)};
			uint Unk3{};
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCt, ASLR(0x00418920), CCamera*, const SCinfo&);

		csl::ut::MoveArray<SCameraListUnit> Units{ GetAllocator() };
		INSERT_PADDING(384) {};

		CCamera(const SCinfo& in_rInfo) : GameObject(true)
		{
			ms_fpCt(this, in_rInfo);
		}
	};
}