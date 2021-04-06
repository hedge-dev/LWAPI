#pragma once

namespace app
{
	class alignas(16) GameObject3D : public GameObject
	{
		// Avoid calling of constructor and destructor
		union
		{
			fnd::GOCTransform m_Transform;
		};
		
		INSERT_PADDING(100){}; // WHAT AND WHY

	protected:
		fnd::GOCTransform* m_pTransform{&m_Transform};

	public:
		GameObject3D() : GameObject()
		{
			new(&m_Transform) fnd::GOCTransform();
			AddComponent(m_pTransform);
		}

		~GameObject3D()
		{
			m_pTransform->~GOCTransform();
		}
		
		bool ProcessMessage(fnd::Message& msg) override
		{
			if (PreProcessMessage(msg))
				return true;

			if (msg.IsOfType<xgame::MsgGetPosition>())
			{
				auto& msgPos = reinterpret_cast<xgame::MsgGetPosition&>(msg);
				const auto& pos = m_Transform.GetLocalPosition();
				msgPos.SetPosition(pos);
				return true;
			}
			else if (msg.IsOfType<xgame::MsgGetRotation>())
			{
				auto& msgRot = reinterpret_cast<xgame::MsgGetRotation&>(msg);
				const auto& rot = m_Transform.GetLocalRotation();
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
