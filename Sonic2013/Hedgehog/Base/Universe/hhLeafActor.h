#pragma once
#include "hhActor.h"

namespace app::fnd
{
	class CLeafActor : public CActor
	{
	public:
		void ForEach(app::fnd::CActorTraverser& traverser) override
		{
			traverser.Callback(*this);
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

			if (enabled)
			{
				return ProcessMessage(*static_cast<Message*>(data));
			}
			
			return false;
		}
	};
}
