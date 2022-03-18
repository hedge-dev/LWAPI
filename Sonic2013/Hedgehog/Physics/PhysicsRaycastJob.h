#pragma once

namespace app::game
{
	using namespace csl::math;
	class PhysicsRaycastJob;

	struct PhysicsRaycastCommand
	{
		Vector3 m_From{};
		Vector3 m_To{};
		uint m_Filter{};
		uint m_Unk1{};
		PhysicsRaycastOutput* m_pResult{};
		uint m_Unk2{};
		bool m_IsHit{};
	};

	class PhysicsRaycastJob : public PhysicsQueryJob
	{
	public:
		csl::ut::InplaceMoveArrayAligned16<PhysicsRaycastCommand, 1> m_Commands{ GetAllocator() };
		void* m_pBuffer{};
		csl::ut::FixedArray<PhysicsRaycastOutput, 2> m_StaticBuffers{};

		PhysicsRaycastJob() : PhysicsQueryJob(Type_Raycast)
		{

		}

		~PhysicsRaycastJob() override
		{
			DeallocateBuffer();
		}

		void Add(const Vector3& in_from, const Vector3& in_to, uint in_filter, uint in_a4, uint in_a5)
		{
			m_Commands.push_back({ in_from, in_to, in_filter, in_a4, nullptr, in_a5 });
		}

		void DeallocateBuffer()
		{
			if (m_pBuffer && m_pBuffer != m_StaticBuffers.begin() && GetAllocator())
			{
				GetAllocator()->Free(m_pBuffer);
				m_pBuffer = nullptr;
			}
		}
	};
}
