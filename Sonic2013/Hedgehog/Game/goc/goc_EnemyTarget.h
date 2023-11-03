#pragma once

namespace app
{
	class GOCEnemyTarget : fnd::GOComponent
	{
	private:
		inline static fnd::GOComponentClass* ms_pGOCEnemyTargetStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FE7608));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x00726510), GOCEnemyTarget*, const Description&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetColliderEyesight, ASLR(0x00726BC0), GOCEnemyTarget*, uint);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetEyesightFrame, ASLR(0x00726310), GOCEnemyTarget*, fnd::HFrame*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetSphereEyesight, ASLR(0x00726AA0), GOCEnemyTarget*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetEyesightOffset, ASLR(0x00726580), GOCEnemyTarget*, const csl::math::Vector3&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetEnableEyesight, ASLR(0x007265C0), GOCEnemyTarget*, bool);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsFindTarget, ASLR(0x00726600), GOCEnemyTarget*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLockTarget, ASLR(0x007266B0), GOCEnemyTarget*);
		inline static FUNCTION_PTR(csl::math::Vector3*, __thiscall, ms_fpGetTargetCenterPosition, ASLR(0x00726610), GOCEnemyTarget*, csl::math::Vector3*);

	public:
		struct Description
		{
			bool IsEnabled{};
		};
		
		static fnd::GOComponentClass* staticClass()
		{
			return ms_pGOCEnemyTargetStaticClass;
		}

		void Setup(const Description& in_rDescription)
		{
			ms_fpSetup(this, in_rDescription);
		}

		void SetColliderEyesight(uint in_unk)
		{
			ms_fpSetColliderEyesight(this, in_unk);
		}

		void SetEyesightFrame(fnd::HFrame* in_pFrame)
		{
			ms_fpSetEyesightFrame(this, in_pFrame);
		}

		void SetSphereEyesight(float in_value)
		{
			ms_fpSetSphereEyesight(this, in_value);
		}

		void SetEyesightOffset(const csl::math::Vector3& in_rOffset)
		{
			ms_fpSetEyesightOffset(this, in_rOffset);
		}

		void SetEnableEyesight(bool in_enable)
		{
			ms_fpSetEnableEyesight(this, in_enable);
		}

		bool IsFindTarget()
		{
			return ms_fpIsFindTarget(this);
		}

		void LockTarget()
		{
			ms_fpLockTarget(this);
		}

		csl::math::Vector3* GetTargetCenterPosition(csl::math::Vector3* out_pPosition)
		{
			return ms_fpGetTargetCenterPosition(this, out_pPosition);
		}
	};
}