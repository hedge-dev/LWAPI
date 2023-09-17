#pragma once

namespace app::game
{
	class MoveCharacterRigidBody : public MoveController
	{
	public:
		enum GravityType : byte;

		struct RangeChecker
		{
			csl::math::Vector3 Position{};
			float Unk2{};
			float Unk3{ -1.0f };
			
			void InitPosition(const csl::math::Vector3& in_rPosition)
			{
				Position = in_rPosition;
			}

			void InitRange(float in_range)
			{
				Unk2 = pow(in_range, 2);
				Unk3 = pow(in_range, 2);
			}
		};

		struct Description
		{
			uint ShapeID{};
			uint FlagBit{};
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpOnEnter, ASLR(0x004C6B80), MoveCharacterRigidBody*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpOnLeave, ASLR(0x004C5FC0), MoveCharacterRigidBody*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x004C6BC0), MoveCharacterRigidBody*, const fnd::SUpdateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004C61C0), MoveCharacterRigidBody*, Description&);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsOnGround, ASLR(0x004C6230), const MoveCharacterRigidBody*);

	public:
		CharacterRigidBodyBase* pRigidBodyBase{};
		PathEvaluator Path{};
		MovementUtility::SideviewInterpolateInfo SideViewInfo{};
		csl::math::Vector3 Unk2{};
		float Unk3{};
		float Unk4{ -1.0f };
		MoveCharacterRigidBody::RangeChecker RangeChecker{};
		BarrierChecker BarrierChecker{};
		MoveStraightCallback StopCallback{};
		MoveStraightCallback RangeOutCallback{};
		csl::ut::Enum<GravityType, byte> GravityType{};
		csl::ut::Bitset<byte> Flags{ 3 };

		DEFINE_RTTI_PTR(ASLR(0x00F6BDE0));

		MoveCharacterRigidBody() : MoveController(MoveControllerType::eMoveControllerType_CharacterRigidBody)
		{
			
		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void OnEnter() override
		{
			ms_fpOnEnter(this);
		}

		void OnLeave() override
		{
			ms_fpOnLeave(this);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ms_fpUpdate(this, in_rUpdateInfo);
		}

		void Setup(Description& in_rDescription)
		{
			ms_fpSetup(this, in_rDescription);
		}

		void SetNotifyStopCallback(MoveStraightCallback in_rCallback)
		{
			StopCallback = in_rCallback;
		}

		void SetNotifyMoveRangeOutCallback(MoveStraightCallback in_rCallback)
		{
			RangeOutCallback = in_rCallback;
		}

		void SetMaxMoveDistance(float in_x, float in_y)
		{
			Unk3 = in_x;
			Unk4 = in_y;
		}

		void SetMoveRange(float in_range)
		{
			RangeChecker.InitRange(in_range);
		}

		void SetMoveRangeBasePosition(const csl::math::Vector3 in_rBasePosition)
		{
			RangeChecker.InitPosition(in_rBasePosition);
			Flags.reset(3);
		}

		bool IsOnGround() const
		{
			return ms_fpIsOnGround(this);
		}
	};
}