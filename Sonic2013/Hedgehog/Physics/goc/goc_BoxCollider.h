#pragma once

namespace app::game
{	
	class GOCBoxColliderCinfo : public ColliBoxShapeCInfo
	{
	public:
		GOCBoxColliderCinfo() : ColliBoxShapeCInfo()
		{
			MotionType = PhysicsMotionType::MotionType::eMotionType_Value2;
			ShapeID = 0;
		}
	};

	class GOCBoxCollider : public GOCColliderSimple
	{
	private:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD75C0));

	public:
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