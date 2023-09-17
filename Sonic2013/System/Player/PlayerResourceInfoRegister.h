#pragma once

namespace app::Player
{
	struct ResourceInfo
	{
		const csl::ut::MoveArray<Game::EPhantomType>* pPhantoms{};
		csl::ut::Bitset<uint> Flags{};
	};

	inline void SetPhantomFlag(Game::EPhantomType in_phantomType, csl::ut::Bitset<uint>* in_pFlags)
	{
		in_pFlags->Set(in_phantomType);
	}

	template <class T>
	void CreateInfo(CObjInfoContainer& in_rContainer, csl::fnd::IAllocator& in_rAlloc)
	{
		CObjInfo* pInfo = new(in_rAlloc) T();
		if (!pInfo)
			return;

		in_rContainer.Register(pInfo->GetInfoName(), pInfo);
	}

	inline void RegisterResourceInfos(GameDocument* in_pDocument, const ResourceInfo& in_rResourceInfo, csl::fnd::IAllocator& in_rAllocator)
	{
		auto* pInfoContainer = in_pDocument->GetService<CObjInfoContainer>();
		CreateInfo<SonicInfo>(*pInfoContainer, in_rAllocator);
		
		if (in_rResourceInfo.Flags.test(2))
			CreateInfo<VirtualSonicInfo>(*pInfoContainer, in_rAllocator);

		if (in_rResourceInfo.Flags.test(4))
			CreateInfo<SonicZeldaInfo>(*pInfoContainer, in_rAllocator);

		if (in_rResourceInfo.Flags.test(0))
			CreateInfo<VehicleTornadoInfo>(*pInfoContainer, in_rAllocator);

		if (in_rResourceInfo.Flags.test(1))
			CreateInfo<VehicleSnowBallInfo>(*pInfoContainer, in_rAllocator);

		csl::ut::Bitset<uint> phantomFlags{};
		for (auto pPhantom : *in_rResourceInfo.pPhantoms)
			SetPhantomFlag(pPhantom, &phantomFlags);

		if (phantomFlags.test(0))
			CreateInfo<PhantomSpinInfo>(*pInfoContainer, in_rAllocator);

		if (phantomFlags.test(1))
			CreateInfo<PhantomLaserInfo>(*pInfoContainer, in_rAllocator);

		if (phantomFlags.test(2))
			CreateInfo<PhantomRocketInfo>(*pInfoContainer, in_rAllocator);

		if (phantomFlags.test(3))
			CreateInfo<PhantomAsteroidInfo>(*pInfoContainer, in_rAllocator);

		if (phantomFlags.test(4))
			CreateInfo<PhantomEagleInfo>(*pInfoContainer, in_rAllocator);

		if (phantomFlags.test(5))
			CreateInfo<PhantomRhythmInfo>(*pInfoContainer, in_rAllocator);

		if (phantomFlags.test(7))
			CreateInfo<PhantomBombInfo>(*pInfoContainer, in_rAllocator);

		if (phantomFlags.test(6))
			CreateInfo<PhantomHoverInfo>(*pInfoContainer, in_rAllocator);

		if (phantomFlags.test(8))
			CreateInfo<PhantomQuakeInfo>(*pInfoContainer, in_rAllocator);

		if (in_rResourceInfo.Flags.test(3))
			CreateInfo<SuperSonicInfo>(*pInfoContainer, in_rAllocator);
	}
}