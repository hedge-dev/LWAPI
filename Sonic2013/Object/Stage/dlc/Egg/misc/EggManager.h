#pragma once

namespace app
{
	namespace egg
	{
		inline size_t GetMaxLocusPositionNum()
		{
			return 121;
		}
	}

	inline EggManager::EggManager() : fnd::GameService(0)
	{
		m_pClass = &EGG_MANAGER;
	}

	inline void EggManager::StartGame(bool a1)
	{
		Loci.clear();
		Loci.set_capacity(egg::GetMaxLocusPositionNum());
		Eggs.clear();
		Eggs.reserve(12);
		ElapsedTime = 0.0f;
		SpaceShrinkFlags.reset();
		FlowerFlags.reset();
	}

	inline void EggManager::Update(const fnd::SUpdateInfo& in_rUpdateInfo)
	{
		UpdateLocusPos(in_rUpdateInfo.deltaTime);
		UpdateEggSpace();
		DoCheckReleaseAllEgg();
		DoCheckClearAllEggEndExtrication();
	}

	inline bool EggManager::AddEgg(GameObjectHandle<ObjEgg> in_egg, size_t* out_pIndex)
	{
		if (Eggs.size() >= 12)
			return false;
		
		*out_pIndex = Eggs.size();
		Eggs.push_back(in_egg);

		return true;
	}

	inline void EggManager::AddSpaceCount()
	{
		for (auto egg : Eggs)
		{
			if (egg.IsValid())
			{
				bool added = egg.Get()->AddSpaceOffset();
				if (added)
					break;
			}
		}

		SpaceShrinkFlags.set(2);
	}

	inline void EggManager::SubSpaceCount()
	{
		for (auto egg : Eggs)
		{
			if (egg.IsValid())
			{
				bool removed = egg.Get()->SubSpaceOffset();
				if (removed)
					break;
			}
		}

		SpaceShrinkFlags.set(2);
	}

	inline bool EggManager::CheckAccessLocusData(size_t in_index, EggManager::LocusData* out_pOutput) const
	{
		size_t lociSize = Loci.size();
		
		if (!lociSize)
			return false;

		if (in_index < lociSize)
			*out_pOutput = Loci.at(in_index);
		else
			*out_pOutput = Loci.back();

		return true;
	}

	inline void EggManager::DoCheckClearAllEggEndExtrication()
	{
		if (!SpaceShrinkFlags.test(1))
			return;

		for (auto egg : Eggs)
		{
			bool ended = egg.Get()->IsEndExtrication();
			if (!ended)
				return;
		}
			
		for (auto egg : Eggs)
			egg.Get()->Kill();

		Eggs.clear();
		SpaceShrinkFlags.reset(1);
	}

	inline void EggManager::DoCheckReleaseAllEgg()
	{
		auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*m_pOwnerDocument, 0);
		if (!pPlayerInfo)
			return;

		if (!pPlayerInfo->IsTimerDisabled)
		{
			SpaceShrinkFlags.reset(3);
			return;
		}

		if (SpaceShrinkFlags.test(3))
			return;

		for (auto egg : Eggs)
			egg.Get()->StartDrop();
		
		Eggs.clear();
		SpaceShrinkFlags.set(3);
	}

	inline EggManager::LocusData EggManager::GetTargetData(size_t in_index, bool* out_pIsValid, float* out_pNorm) const
	{
		return GetTargetDataFromLocusIndex(GetTargetLocusIndex(in_index), out_pIsValid, out_pNorm);
	}

	inline size_t EggManager::GetTargetLocusIndex(size_t in_index) const
	{
		size_t index{};

		for (size_t i = 0; i <= in_index; i++)
		{
			if (Eggs[i].IsValid())
				index += Eggs[i].Get()->SpaceOffset;
		}

		return index;
	}

	inline EggManager::LocusData EggManager::GetTargetDataFromLocusIndex(size_t in_index, bool* out_pIsValid, float* out_pNorm) const
	{
		EggManager::LocusData previousLocus{};
		EggManager::LocusData currentLocus{};
			
		if (CheckAccessLocusData(in_index, &currentLocus))
		{
			if (!out_pIsValid)
				return currentLocus;
			
			if ((int)in_index - 1 < 0)
				return currentLocus;
				
			if (!CheckAccessLocusData(in_index - 1, &previousLocus))
				return currentLocus;
			
			csl::math::Vector3 positionOffset = { currentLocus.Position - previousLocus.Position };
			float offset = positionOffset.norm();
			if (offset > 0.3f && (ElapsedTime > 0.0f || SpaceShrinkFlags.test(2)))
			{
				*out_pIsValid = true;
				if (out_pNorm)
					*out_pNorm = offset;
			}
		}

		return currentLocus;
	}

	inline bool EggManager::IsEndExtrication() const
	{
		return Eggs.size() == 0;
	}

	inline bool EggManager::IsLocusDataInGroundToAir() const
	{
		bool result{};
		bool isInAir{};

		for (size_t i = 0; i <= Eggs.size() * 10; i++)
		{
			EggManager::LocusData locus{};

			if (CheckAccessLocusData(i, &locus))
			{
				if (locus.IsAirborne)
				{
					if (isInAir)
						result = true;
				}
				else
				{
					isInAir = true;
				}
			}
		}

		return result;
	}

	inline bool EggManager::IsYoshiSpecialFlowerTaked(size_t in_index) const
	{
		return FlowerFlags.test(in_index);
	}

	inline void EggManager::TakeYoshiSpecialFlower(size_t in_index)
	{
		FlowerFlags.set(in_index);
	}

	inline void EggManager::SetForceSpaceShrink(bool in_isShrink)
	{
		SpaceShrinkFlags.set(0, in_isShrink);
	}

	inline void EggManager::StartExtrication()
	{
		for (auto egg : Eggs)
			egg.Get()->StartExtrication();
		
		SpaceShrinkFlags.set(1);
	}

	inline void EggManager::UpdateEggSpace()
	{
		SpaceShrinkFlags.reset(2);
		auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*m_pOwnerDocument, 0);
		if (pPlayerInfo && pPlayerInfo->IsLandOnMovableGround)
		{
			SubSpaceCount();
			return;
		}

		if (SpaceShrinkFlags.test(0))
		{
			SubSpaceCount();
			return;
		}

		if (ElapsedTime > 0.0f)
			AddSpaceCount();
	}

	inline void EggManager::UpdateLocusPos(float in_delta)
	{
		auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*m_pOwnerDocument, 0);
		if (!pPlayerInfo)
			return;

		if (Loci.size() <= 1)
		{
			EggManager::LocusData locus{};
			locus.Position = pPlayerInfo->Position;
			locus.Rotation = pPlayerInfo->Rotation;
			locus.IsAirborne = !pPlayerInfo->IsOnGround;

			Loci.push_front(locus);
			return;
		}

		float firstLocusDist = csl::math::Vector3(pPlayerInfo->Position - Loci.at(0).Position).squaredNorm();
		float secondLocusDist = csl::math::Vector3(Loci.at(0).Position - Loci.at(1).Position).squaredNorm();

		if (firstLocusDist >= 0.09f || (firstLocusDist - secondLocusDist) > 0.000001f)
		{
			ElapsedTime = 0.3f;
			EggManager::LocusData locus{};
			locus.Position = pPlayerInfo->Position;
			locus.Rotation = pPlayerInfo->Rotation;
			locus.IsAirborne = !pPlayerInfo->IsOnGround;

			Loci.push_front(locus);
			return;
		}
		
		ElapsedTime -= in_delta;
		if (ElapsedTime >= 0.0f || IsLocusDataInGroundToAir())
		{
			EggManager::LocusData locus{};
			locus.Position = pPlayerInfo->Position;
			locus.Rotation = pPlayerInfo->Rotation;
			locus.IsAirborne = !pPlayerInfo->IsOnGround;

			Loci.push_front(locus);
			return;
		}
	}
}