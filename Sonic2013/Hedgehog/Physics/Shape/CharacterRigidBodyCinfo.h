#pragma once

namespace app::game
{
	class alignas(16) CharacterRigidBodyCinfo : public CollisionObjCinfo
	{
	public:
		float Unk7{};
		float Unk8{};
		float Unk9{ 0.78539819f };
		float Unk10{ 1000.0f };
		float Unk11{ 1 };
	};
}