#pragma once

namespace app
{
	class EnemySweepMove
	{
	public:
		CPhysicsWorld* pWorld{};
		float Unk1{};
		float Unk2{};
		int CollisionFilter{ 0xC996 };
		GameObjectHandle<GameObject> Object{};

		void Setup(CPhysicsWorld* in_pWorld, float in_unk1, float in_unk2)
		{
			pWorld = in_pWorld;
			Unk1 = in_unk1;
			Unk2 = in_unk2;
		}
	};
}