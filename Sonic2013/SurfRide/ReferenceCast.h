#pragma once

namespace SurfRide
{
	struct SRS_REFERENCECAST
	{
		SRS_LAYER* m_pLayer{};
		int m_Unk1{};
		int m_AnimationID{};
		int m_AnimationFrame{};
		int m_Unk2{};
	};

	class ReferenceCast
	{
	public:
		SRS_REFERENCECAST* m_pBinaryNode{};
		Layer* m_rcLayer {}; // SurfRide::ReferenceCount<Layer>
		int m_AnimationID{};
		float m_AnimationFrame{};
		int m_Unk1{};
		int m_Unk2{};

		virtual ~ReferenceCast() = 0;
	};
}