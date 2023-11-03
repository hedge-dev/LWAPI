#pragma once

namespace app::fnd
{
	class CBranchActor : public CActor
	{
	protected:
		csl::ut::MoveArray<CActor*> m_ChildActors { 1024, game::GlobalAllocator::GetAllocator(2) };
		csl::ut::MoveArray<CActor*> m_PhasedActors[3];

	public:
		CBranchActor()
		{
			for (size_t i = 0; i < 3; i++)
			{
				m_PhasedActors[i] = csl::ut::MoveArray<CActor*>(1024, game::GlobalAllocator::GetAllocator(2));
			}
		}

		void AddChild(CActor* in_pActor)
		{
			m_ChildActors.push_back(in_pActor);
			for (size_t i = 0; i < 3; i++)
				if (in_pActor->GetUpdateFlag(i))
					m_PhasedActors[i].push_back(in_pActor);

			in_pActor->SetParent(this);
		}
		
		size_t ForEach(CActorTraverser& in_rTraverser) override
		{
			auto count = in_rTraverser.Callback(*this);
			if (count)
				return count == 1;

			for (auto& pActor : m_ChildActors)
			{
				pActor->ForEach(in_rTraverser);
			}
			
			return 1;
		}
	};
}