#pragma once

namespace app
{
	struct SDroppedRingInfo
	{
		csl::math::Vector3 Position{};
		int RingCount{};
		bool DroppedByPlayer{};
		bool Is2D{};
		char Unk5{};
		float Unk6{ 1.0f };
		float LifeSpan{ 1.0f };
	};
}

namespace app::dropped_ring
{
	inline void Create(GameDocument& in_rDocument, const SDroppedRingInfo& in_rInfo)
	{
		CObjDroppedRing::SUniqueInfo uniqueInfo{};
		csl::math::Vector3 gravityDir{ 0.0f, -1.0f, 0.0f };
		csl::math::Quaternion rotation{ csl::math::Quaternion::Identity };

		auto* pLevelInfo = in_rDocument.GetService<CLevelInfo>();
		bool isYoshiLevel = strcmp(pLevelInfo->Level, "zdlc02") == 0;
		if (isYoshiLevel)
		{
			ObjUtil::PlaySE2D("obj_yossycoin_lost", { HH_SOUND_DEVICE_AUTO });
		}
		else if (in_rInfo.DroppedByPlayer)
		{
			ObjUtil::PlaySE2D("obj_ringspread", { HH_SOUND_DEVICE_AUTO });
		}
		else
		{
			ObjUtil::PlaySE2D("obj_ringspread2", { HH_SOUND_DEVICE_AUTO });
		}

		if (!in_rInfo.Unk5)
		{
			if (auto* pGravityManager = in_rDocument.GetService<game::GravityManager>())
			{
				if (auto* pGravityField = pGravityManager->GetObjectAtPoint(in_rInfo.Position))
				{
					if (pGravityField->GetDirection(in_rInfo.Position, &gravityDir))
					{
						csl::math::QuaternionRotationBetweenNormals(&rotation, { 0.0f, -1.0f, -0.0f }, gravityDir);
					}
				}
			}
		}

		uniqueInfo.Counter = 0;
		if (in_rInfo.Is2D)
		{
			game::PathRaycastInput rayInput{};
			rayInput.From = csl::math::Vector3(in_rInfo.Position - gravityDir * 3.0f);
			rayInput.To = csl::math::Vector3(in_rInfo.Position + gravityDir * 400.0f);
			rayInput.Unk1 = 1;
			rayInput.Unk2 = 1;

			game::PathRaycastOutput rayOutput{};

			if (auto* pPathManager = in_rDocument.GetService<game::PathManager>())
			{
				if (pPathManager->CastRay(rayInput, &rayOutput))
				{
					uniqueInfo.PathEvaluator.SetPathObject(rayOutput.pComponent);
					uniqueInfo.PathEvaluator.SetDistance(rayOutput.Distance);
					uniqueInfo.Flags.set(CObjDroppedRing::SUniqueInfo::FLAG_IS_2D, true);
				}
			}
		}

		uniqueInfo.Position = in_rInfo.Position;;
		uniqueInfo.Flags.set(CObjDroppedRing::SUniqueInfo::FLAG_DROPPED_BY_PLAYER, in_rInfo.DroppedByPlayer);
		uniqueInfo.Flags.set(4, in_rInfo.Unk5);
		uniqueInfo.Flags.set(CObjDroppedRing::SUniqueInfo::FLAG_IS_YOSHI_LEVEL, isYoshiLevel);
		uniqueInfo.Unk2 = 0.8f;
		uniqueInfo.Unk3 = 0.75f;
		uniqueInfo.LifeSpan = in_rInfo.LifeSpan;

		if (!in_rInfo.RingCount)
			return;

		if (uniqueInfo.PathEvaluator.Component.IsValid())
		{
			bool isEven = (in_rInfo.RingCount & 1) == 0;
			float magicNumber = -(MATHF_PI * 2 * 0.1f * ((in_rInfo.RingCount >> 1) - isEven + 0.5f));

			float fakeRandom = 1.0f;
			if (in_rInfo.RingCount > 10)
			{
				int tenRingCount = (in_rInfo.RingCount - 1) / 10;
				fakeRandom = tenRingCount * 0.3 + 0.7f;
			}

			float scalar{};
			for (size_t i = 0; i < in_rInfo.RingCount;)
			{
				uniqueInfo.Unk1 = { (uniqueInfo.PathEvaluator.GetTangent(uniqueInfo.PathEvaluator.Distance) * in_rInfo.Unk6 * sinf(magicNumber) +
										-gravityDir * cosf(magicNumber)) * (150.0f * -(0.3f * scalar - fakeRandom)) };

				auto* pObject = new CObjDroppedRing(uniqueInfo);
				if (!pObject)
					continue;

				in_rDocument.AddGameObject(pObject);
				if (++uniqueInfo.Counter >= 3)
					uniqueInfo.Counter = 0;

				if ((++i % 10) == 0)
				{
					magicNumber += MATHF_PI;
					scalar += 1.0f;
				}

				magicNumber += MATHF_PI * 2 * 0.1f;
			}

			return;
		}

		float random = SonicUSA::System::Random::GetInstance()->genrand_float32();
		float magicNumber = random * MATHF_PI * 2;

		for (size_t i = 0; i < in_rInfo.RingCount; i++)
		{
			csl::math::Vector3 vector{ csl::math::Vector3(sinf(magicNumber), 0.0f, cosf(magicNumber)) * 40.0f * in_rInfo.Unk6 };
			vector.y() = 100.f;

			uniqueInfo.Unk1 = math::Vector3Rotate(rotation, vector);

			auto* pObject = new CObjDroppedRing(uniqueInfo);
			if (!pObject)
				continue;

			in_rDocument.AddGameObject(pObject);
			if (++uniqueInfo.Counter >= 3)
				uniqueInfo.Counter = 0;

			magicNumber += ((MATHF_PI * 2) / in_rInfo.RingCount);
		}
	}
}