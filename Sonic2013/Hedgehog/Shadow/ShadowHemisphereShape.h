#pragma once

namespace app::game
{
	class ShadowHemisphereShapeCInfo : public ShadowShapeCInfo
	{
	public:
		float Radius{};

		ShadowHemisphereShapeCInfo(float in_radius) : ShadowShapeCInfo(1), Radius(in_radius)
		{

		}
	};
}