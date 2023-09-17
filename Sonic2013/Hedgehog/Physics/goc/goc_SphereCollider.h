#pragma once

namespace app::game
{	
	class GOCSphereColliderCinfo : public ColliSphereShapeCInfo
	{
	public:
		INSERT_PADDING(8) {};

		GOCSphereColliderCinfo() : ColliSphereShapeCInfo()
		{
			m_MotionType = PhysicsMotionType::MotionType::MotionType_VALUE2;
			m_ShapeID = 0;
		}
	};

	class GOCSphereCollider : public GOCColliderSimple
	{
	public:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7614));

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		bool Setup(const GOCSphereColliderCinfo& in_rCreateInfo)
		{
			return CreateShape(in_rCreateInfo) != nullptr;
		}
	};
}