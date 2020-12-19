#pragma once

namespace app
{
	class alignas(16) GameObject3D : public GameObject
	{
		fnd::GOCTransform transform;
		INSERT_PADDING(100); // WHAT AND WHY

	protected:
		fnd::GOCTransform* pTransform{&transform};

	public:
		GameObject3D() : GameObject()
		{
			AddComponent(pTransform);
		}

		bool ProcessMessage(fnd::Message& msg) override
		{
			if (PreProcessMessage(msg))
				return true;

			if (msg.IsOfType<xgame::MsgGetPosition>())
			{
				auto& msgPos = reinterpret_cast<xgame::MsgGetPosition&>(msg);
				const auto& pos = transform.GetLocalPosition();
				msgPos.SetPosition(pos);
				return true;
			}
			else if (msg.IsOfType<xgame::MsgGetRotation>())
			{
				auto& msgRot = reinterpret_cast<xgame::MsgGetRotation&>(msg);
				const auto& rot = transform.GetLocalRotation();
				msgRot.SetRotation(rot);
				return true;
			}
			else if (msg.IsOfType<xgame::MsgDeactivate>())
			{
				isDeactivated = true;
				Kill();
				return true;
			}
			
			return GameObject::ProcessMessage(msg);
		}
	};
}
