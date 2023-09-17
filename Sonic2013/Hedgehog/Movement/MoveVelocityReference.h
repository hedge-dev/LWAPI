#pragma once

namespace app::game
{
	class MoveVelocityReference : public MoveController
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x004C9DC0), MoveVelocityReference*, const fnd::SUpdateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupGravityPath, ASLR(0x004C9F70), MoveVelocityReference*);

	public:
		game::MovementUtility::SideviewInterpolateInfo SideViewInfo{};
		game::PathEvaluator GravityPath{};
		int GravityType{};
		csl::math::Vector3 GravityFieldPosition{};
		bool IsFixedHeight{};

		DEFINE_RTTI_PTR(ASLR(0x00F6BF10));

		MoveVelocityReference() : MoveController(MoveControllerType::eMoveControllerType_VelocityReference)
		{

		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void OnEnter() override
		{
			SetupGravityPath();
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ms_fpUpdate(this, in_rUpdateInfo);
		}

		void SetupGravityPath()
		{
			ms_fpSetupGravityPath(this);
		}

		void SetFixedHeight(bool in_enable)
		{
			IsFixedHeight = in_enable;
		}

		void SetNoneGravity(bool in_enable)
		{
			GravityType = in_enable;
		}
	};
}