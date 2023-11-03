#pragma once

namespace SurfRide
{
	struct SRS_TRS_BASE
	{
		Color MaterialColor{};
		Color IlluminationColor{};
		bool Display{};
	};

	struct SRS_TRS2D : public SRS_TRS_BASE
	{
		Math::Vector2 Translation{};
		uint Rotation{};
		Math::Vector2 Scale{};
	};

	struct SRS_TRS3D : public SRS_TRS_BASE
	{
		Math::Vector3 Translation{};
		uint Rotation[3]{};
		Math::Vector3 Scale{};
	};

	struct SRS_CASTNODE
	{
		const char* pName{};
		int ID{};
		int Flags{};
		void* pData{};
		short ChildIndex{};
		short SiblingIndex{};
		void* pUserData{};
	};

	class Transform : public Base
	{
	public:
		virtual ~Transform() = default;

		INSERT_PADDING(8);
		Color MaterialColor{};
		Color IlluminationColor{};
		bool Display{};
		int DirtyFlag{}; // Dirty Flag
		INSERT_PADDING(8);
	};
}