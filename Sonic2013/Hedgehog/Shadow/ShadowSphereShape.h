#pragma once

namespace app::game
{
	class ShadowSphereShapeCInfo : public ShadowShapeCInfo
	{
	public:
		float Radius{};

		ShadowSphereShapeCInfo(float in_radius) : ShadowShapeCInfo(0), Radius(in_radius)
		{

		}
	};
}