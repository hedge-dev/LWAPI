#pragma once

namespace app::game
{	
	class GOCSphereColliderCinfo : public ColliSphereShapeCInfo
	{
	public:
		INSERT_PADDING(8) {};

		GOCSphereColliderCinfo() : ColliSphereShapeCInfo()
		{
			MotionType = PhysicsMotionType::MotionType::eMotionType_Value2;
			ShapeID = 0;
		}
	};

	class GOCSphereCollider : public GOCColliderSimple
	{
	private:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7614));

	public:
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