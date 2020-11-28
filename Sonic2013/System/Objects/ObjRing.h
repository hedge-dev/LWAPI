#pragma once
#include <System/GameObject.h>
#include <System/ObjectSystem/SetObjectListener.h>

namespace app
{
	class ObjRing : public CSetObjectListener
	{
	public:
		bool ProcessMessage(app::xgame::Message& message) override
		{
			return true;
		}

		bool PreProcessMessage(app::xgame::Message& message) override
		{
			return true;
		}

		void Update(const app::fnd::SUpdateInfo& updateInfo) override
		{

		}
	};
}