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
		
		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			if (in_rMessage.IsOfType<xgame::MsgGetPosition>())
			{
				auto& msgPos = reinterpret_cast<xgame::MsgGetPosition&>(in_rMessage);
				csl::math::Vector3 pos = m_Transform.GetLocalPosition();
				msgPos.SetPosition(pos);
				return true;
			}
			else if (in_rMessage.IsOfType<xgame::MsgGetRotation>())
			{
				auto& msgRot = reinterpret_cast<xgame::MsgGetRotation&>(in_rMessage);
				csl::math::Quaternion rot = m_Transform.GetLocalRotation();
				msgRot.SetRotation(rot);
				return true;
			}
			else if (in_rMessage.IsOfType<xgame::MsgDeactivate>())
			{
				auto& msgDeactivate = reinterpret_cast<xgame::MsgDeactivate&>(in_rMessage);
				msgDeactivate.m_Handled = true;
				Kill();
				return true;
			}
			
			return GameObject::ProcessMessage(in_rMessage);
		}
	};
}