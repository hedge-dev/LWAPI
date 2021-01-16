#pragma once

namespace app::fnd
{
	class CBranchActor : public CActor
	{
	protected:
		csl::ut::MoveArray<CActor*> m_ChildActors { 1024, game::GlobalAllocator::GetSingletonAllocator() };
		csl::ut::MoveArray<CActor*> m_PhasedActors[3];

	public:
		CBranchActor()
		{
			for (auto& m_PhasedActor : m_PhasedActors)
			{
				m_PhasedActor = csl::ut::MoveArray<CActor*>(game::GlobalAllocator::GetSingletonAllocator());
			}
		}
	};
}