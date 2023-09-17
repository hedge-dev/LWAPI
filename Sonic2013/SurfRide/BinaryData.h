#pragma once

namespace SurfRide
{
	class BinaryData : public Base
	{
	public:
		virtual ~BinaryData() = default;

		void* pBinaryData{};
		int RefCount{};

		void IncrementReferenceCount()
		{
			RefCount++;
		}

		void DecrementReferenceCount()
		{
			RefCount--;
		}

		int GetReferenceCount()
		{
			return RefCount;
		}

		void DeleteData()
		{

		}

		void Cleanup()
		{
			if (pBinaryData)
				DeleteData();
		}
	};
}