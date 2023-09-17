#pragma once

namespace SurfRide
{
	enum SRE_CURVE_TYPE : ushort
	{
		eCurveType_TranslationX,
		eCurveType_TranslationY,
		eCurveType_TranslationZ,
		eCurveType_RotationX,
		eCurveType_RotationY,
		eCurveType_RotationZ,
		eCurveType_ScaleX,
		eCurveType_ScaleY,
		eCurveType_ScaleZ,
		eCurveType_MaterialColor,
		eCurveType_Display,
		eCurveType_Width,
		eCurveType_Height,
		eCurveType_VertexColorTopLeft,
		eCurveType_VertexColorTopRight,
		eCurveType_VertexColorBottomLeft,
		eCurveType_VertexColorBottomRight,
		eCurveType_CropIndex0,
		eCurveType_CropIndex1,
		eCurveType_Unknown,
		eCurveType_IlluminationColor,
		eCurveType_MaterialColorR,
		eCurveType_MaterialColorG,
		eCurveType_MaterialColorB,
		eCurveType_MaterialColorA,
		eCurveType_VertexColorTopLeftR,
		eCurveType_VertexColorTopLeftG,
		eCurveType_VertexColorTopLeftB,
		eCurveType_VertexColorTopLeftA,
		eCurveType_VertexColorTopRightR,
		eCurveType_VertexColorTopRightG,
		eCurveType_VertexColorTopRightB,
		eCurveType_VertexColorTopRightA,
		eCurveType_VertexColorBottomLeftR,
		eCurveType_VertexColorBottomLeftG,
		eCurveType_VertexColorBottomLeftB,
		eCurveType_VertexColorBottomLeftA,
		eCurveType_VertexColorBottomRightR,
		eCurveType_VertexColorBottomRightG,
		eCurveType_VertexColorBottomRightB,
		eCurveType_VertexColorBottomRightA,
		eCurveType_IlluminationColorR,
		eCurveType_IlluminationColorG,
		eCurveType_IlluminationColorB,
		eCurveType_IlluminationColorA,
	};

	union SRU_FRAME_TYPE
	{
		int Int;
		bool Boolean;
		char Character;
		float Float;
		Color Color;
	};

	struct SRS_KEYFRAME
	{
		int Frame{};
		SRU_FRAME_TYPE Value{};
	};

	struct SRS_TRACK
	{
		SRE_CURVE_TYPE TrackType{};
		short KeyCount{};
		uint Flags{};
		uint FirstFrame{};
		uint LastFrame{};
		SRS_KEYFRAME* pKeyFrame{};
	};

	struct SRS_MOTION
	{
		ushort CastId{};
		short TrackCount{};
		SRS_TRACK* pTracks{};
	};

	struct alignas(4) SRS_ANIMATION
	{
		const char* pName{};
		int ID{};
		int LinkCount{};
		int FrameCount{};
		SRS_MOTION* pLinks{};
		void* pUserData{};
		bool IsLooping{};
	};
}