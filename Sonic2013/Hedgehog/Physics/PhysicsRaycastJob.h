#pragma once

namespace app::game
{
	using namespace csl::math;
	class PhysicsRaycastJob;

	struct PhysicsRaycastCommand
	{
		Vector3 From{};
		Vector3 To{};
		uint Filter{};
		uint Unk1{};
		PhysicsRaycastOutput* pResult{};
		uint Unk2{};
		bool IsHit{};
	};

	class PhysicsRaycastJob : public PhysicsQueryJob
	{
	public:
		csl::ut::InplaceMoveArrayAligned16<PhysicsRaycastCommand, 1> Commands{ GetAllocator() };
		void* pBuffer{};
		csl::ut::FixedArray<PhysicsRaycastOutput, 2> StaticBuffers{};

		PhysicsRaycastJob() : PhysicsQueryJob(eType_Raycast)
		{

		}

		~PhysicsRaycastJob() override
		{
			DeallocateBuffer();
		}

		void Add(const Vector3& in_rFrom, const Vector3& in_rTo, uint in_filter, uint in_a4, uint in_a5)
		{
			Commands.push_back({ in_rFrom, in_rTo, in_filter, in_a4, nullptr, in_a5 });
		}

		void DeallocateBuffer()
		{
			if (pBuffer && pBuffer != StaticBuffers.begin() && GetAllocator())
			{
				GetAllocator()->Free(pBuffer);
				pBuffer = nullptr;
			}
		}

		void Reserve(int in_amount)
		{
			Commands.reserve(in_amount);
		}

		void Clear()
		{
			Commands.clear();
		}
	};
}
