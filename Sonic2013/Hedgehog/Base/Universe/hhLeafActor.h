#pragma once

namespace app::fnd
{
	class CLeafActor : public CActor
	{
	public:
		size_t ForEach(app::fnd::CActorTraverser& traverser) override
		{
			return traverser.Callback(*this);
		}

		bool ActorProc(int id, void* data) override
		{
			if (id < 0)
				return false;

			if (id > 1)
			{
				if (id == 3)
					Update(*static_cast<SUpdateInfo*>(data));

				return true;
			}

			if (m_Enabled)
			{
				return ProcessMessage(*static_cast<Message*>(data));
			}

			return false;
		}
	};
}
