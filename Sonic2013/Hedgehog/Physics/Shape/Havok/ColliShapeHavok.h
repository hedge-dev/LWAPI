#pragma once

namespace app::game
{
	class ColliShapeHavok : public ColliShapeBase
	{
	public:
		INSERT_PADDING(144){};
	};

	class ColliShape : public ColliShapeHavok {};
}