#pragma once

namespace app::fnd
{
	class CLeafActor : public CActor
	{
	public:
		size_t ForEach(app::fnd::CActorTraverser& in_rTraverser) override
		{
			return in_rTraverser.Callback(*this);
		}

		bool ActorProc(int in_id, void* in_pData) override
		{
			if (in_id < 0)
				return false;

			if (in_id > 1)
			{
				if (in_id == 3)
					Update(*static_cast<SUpdateInfo*>(in_pData));

				return true;
			}

			if (Enabled)
			{
				return ProcessMessage(*static_cast<Message*>(in_pData));
			}

			return false;
		}
	};
}
