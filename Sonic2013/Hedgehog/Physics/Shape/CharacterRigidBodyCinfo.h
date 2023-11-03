#pragma once

namespace app::game
{
	class alignas(16) CharacterRigidBodyCinfo : public CollisionObjCinfo
	{
	public:
		float m_Unk7{};
		float m_Unk8{};
		float m_Unk9{ 0.78539819f };
		float m_Unk10{ 1000.0f };
		float m_Unk11{ 1 };
	};
}