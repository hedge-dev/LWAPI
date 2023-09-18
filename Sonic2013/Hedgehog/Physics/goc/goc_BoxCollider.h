#pragma once

namespace app::game
{	
	class GOCBoxColliderCinfo : public ColliBoxShapeCInfo
	{
	public:
		GOCBoxColliderCinfo() : ColliBoxShapeCInfo()
		{
			m_MotionType = PhysicsMotionType::MotionType::MotionType_VALUE2;
			m_ShapeID = 0;
		}
	};

	class GOCBoxCollider : public GOCColliderSimple
	{
	public:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD75C0));

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		bool Setup(const GOCBoxColliderCinfo& in_rCreateInfo)
		{
			return CreateShape(in_rCreateInfo) != nullptr;
		}
	};
}