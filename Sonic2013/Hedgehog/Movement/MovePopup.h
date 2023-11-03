#pragma once

namespace app::game
{
	class MovePopup : public MoveController
	{
	public:
		struct SDesc
		{
			float Unk1{ 130.f };
			float Unk2{ 550.0f };
			float Unk3{};
			csl::ut::Bitset<uint8> Unk4{};
		};

		csl::math::Vector3 Position{};
		csl::math::Quaternion Rotation{};
		SDesc Description{};
		float Unk5{};
		float Unk6{};
		float Unk7{};
		float Unk8{};

		MovePopup() : MoveController(MoveControllerType::eMoveControllerType_Popup)
		{
			
		}

		void OnEnter() override
		{
			Unk5 = Description.Unk1;
			Unk6 = Description.Unk3;
			Unk7 = 0.0f;
			Unk8 = 0.0f;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (Unk5 <= 0.0f)
			{
				Unk8 += in_rUpdateInfo.DeltaTime;
			}
			else
			{
				Unk5 = -(Description.Unk2 * in_rUpdateInfo.DeltaTime) - Unk5;
				if (Unk5 <= 0.0f)
					Unk5 = 0.0f;
			}
			
			auto* pMovement = GetOwnerMovement();
			if (!pMovement)
				return;

			auto* pContextParam = pMovement->GetContextParam();
			if (!pContextParam)
				return;

			auto vecOffset = app::math::Vector3Rotate(pContextParam->Rotation, static_cast<csl::math::Vector3>(csl::math::Vector3::UnitY()));
			pContextParam->Velocity = static_cast<csl::math::Vector3>(vecOffset * Unk5);
			Unk6 += Unk5 * in_rUpdateInfo.DeltaTime;

			pContextParam->Position = static_cast<csl::math::Vector3>(Position + (vecOffset * Unk6));

			if (!Description.Unk4.test(0))
				Unk7 = csl::math::Lerp<float>(10, 15, Unk5 / Description.Unk1) * in_rUpdateInfo.DeltaTime;
			
			csl::math::Quaternion rotOffset(Eigen::AngleAxisf(Unk7, Eigen::Vector3f::UnitY()));
			pContextParam->Rotation = Rotation * rotOffset;
		}
		
	private:
		// This is the original function name by Sonic Team.
		void SetBaseTransfrom(const csl::math::Vector3& in_rPos, const csl::math::Quaternion& in_rRot)
		{
			Position = in_rPos;
			Rotation = in_rRot;
		}

	public:
		inline void SetBaseTransform(const csl::math::Vector3& in_rPos, const csl::math::Quaternion& in_rRot) { SetBaseTransfrom(in_rPos, in_rRot); }

		void Setup(const SDesc& in_rDescription)
		{
			Description = in_rDescription;
		}
	};
}