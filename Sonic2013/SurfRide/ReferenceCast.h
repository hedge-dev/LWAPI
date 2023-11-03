#pragma once

namespace SurfRide
{
	struct SRS_REFERENCECAST
	{
		SRS_LAYER* pLayer{};
		int Unk1{};
		int AnimationID{};
		int AnimationFrame{};
		int Unk2{};
	};

	class ReferenceCast
	{
	public:
		SRS_REFERENCECAST* pBinaryNode{};
		Layer* rcLayer {}; // SurfRide::ReferenceCount<Layer>
		int AnimationID{};
		float AnimationFrame{};
		int Unk1{};
		int Unk2{};

		virtual ~ReferenceCast() = 0;
	};
}