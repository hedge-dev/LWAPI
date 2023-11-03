#pragma once

namespace app::game
{
	class GOCMotorRotate : public GOCMotor
	{
	private:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD77D4));

	public:
		struct Description
		{
			csl::math::Vector3 Unk1{};
			float Omega{ 0.1 };
			float Offset{};
			TimeType Type{};
		};

		csl::math::Vector3 Unk1{};
		float Omega{ 0.1f };
		float Offset{};
		TimeType Type{};

		GOCMotorRotate() : GOCMotor()
		{
			Flags = 14;
		}

		void Actuate(float in_time, UpdateOutput* out_pOutput) override
		{
			csl::math::Quaternion q(Eigen::AngleAxisf(Omega * in_time + Offset, Unk1));
			out_pOutput->Rotation = Transform.Rotation * q;
			out_pOutput->SetFlag(1);
		}

		void DrawDebugDraw() override
		{
			Transform.Position + math::Vector3Rotate(Transform.Rotation, Unk1) * 4.0f * 10.0f;
		}

		void SetParameters(const Description& in_rDescription)
		{
			Unk1 = in_rDescription.Unk1;
			Omega = in_rDescription.Omega;
			Offset = in_rDescription.Offset;
			Type = in_rDescription.Type;

			if (fabs(Omega) <= 0.000001f)
				SetTimeParameter(Type, 0.1f);
			else
				SetTimeParameter(Type, MATHF_PI * 2 / Omega);
		}
			
		void Setup(const Description& in_rDescription)
		{
			SetParameters(in_rDescription);
			InitTransform();
		}

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
	};
}