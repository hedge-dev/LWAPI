#pragma once

namespace app::game
{	
	class GOCColliderSimple : public GOCCollider
	{
	public:
		GOCColliderSimple() : GOCCollider()
		{
			unk1 |= 1;
		}

		ColliShape* CreateShape(const ColliShapeCInfo& in_rCreateInfo)
		{
			return GOCCollider::CreateShape(in_rCreateInfo);
		}
	};
}