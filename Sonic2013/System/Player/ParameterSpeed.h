#pragma once

namespace app::Player
{
	class CParameterSpeed
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCalcMaxVelocity, ASLR(0x008669E0), CParameterSpeed*, const float&, const float&);

	public:
		enum EGroundStatus;

		CPlayer* pPlayer{};
		float Unk1{};
		float Unk2{};
		float Unk3{ 1.0f };
		float Unk4{ 1.0f };
		csl::ut::Bitset<uint> Unk5{};
		EGroundStatus GroundStatus{};

		void SetGroundStatus(EGroundStatus in_status)
		{
			GroundStatus = in_status;
		}

		void SetSpeedUp(bool in_enable)
		{
			Unk5.set(7, in_enable);
		}

		void SetSlowDown(bool in_enable)
		{
			Unk5.set(8, in_enable);
		}

		void CalcMaxVelocity(const float& in_unk1, const float& in_unk2)
		{
			ms_fpCalcMaxVelocity(this, in_unk1, in_unk2);
		}

		void UpdateMaxVelocity()
		{
			CalcMaxVelocity(Unk1, Unk2);
			Unk1 = csl::math::Min(Unk1, 1450.0f);
		}

		void UpdateAcceleration()
		{
			Unk4 = 1.0f;
		}

		void Update()
		{
			if (!Unk5.test(6))
			{
				UpdateMaxVelocity();
				UpdateAcceleration();
			}
		}
	};
}