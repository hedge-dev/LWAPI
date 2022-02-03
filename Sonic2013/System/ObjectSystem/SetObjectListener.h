#pragma once

namespace app
{
	class CSetAdapter;
	
	class CSetObjectListener : public GameObject3D
	{
	protected:
		CSetObjectManager* m_pSetObjectManager{};
		CSetAdapter* m_pAdapter{};
		CMyActivationHandle m_ActivationHandle{};
	public:
		csl::ut::LinkListNode m_ListNode;
		
	public:
		CSetObjectListener()
		{
			ASSERT_OFFSETOF(CSetObjectListener, m_ActivationHandle, 816);
			ASSERT_OFFSETOF(CSetObjectListener, m_ListNode, 912);

			m_ActivationHandle.SetOwner(this);
		}

		~CSetObjectListener()
		{
			if (m_pSetObjectManager)
				m_pSetObjectManager->RemoveListener(this);
		}
		
	protected:
		bool ProcessMessage(fnd::Message& msg) override
		{
			if (PreProcessMessage(msg))
				return true;

			if (msg.IsOfType<SetEd::MsgUpdateSetEditor>() || msg.IsOfType<SetEd::MsgSetObjectEdited>())
			{
				return true;
			}

			return GameObject3D::ProcessMessage(msg);
		}
		
		virtual void OnInitializedSetObject()
		{
			
		}
		
		virtual void OnPutSetObject(CSetAdapter& adapter)
		{
			
		}
		
		virtual void OnSetEditorParamChanged(CSetAdapter& adapter)
		{

		}

	public:
		virtual unsigned int GetAdsorbGuidePathID()
		{
			return 0;
		}

		virtual double GetAdsorbPathPosition()
		{
			return -1.0;
		}

		virtual csl::math::Vector3 GetAdsorbPathOffset()
		{
			return { 0, 0, 0 };
		}

		
		virtual void SetAppearance(float opacity) // not sure if this is opacity
		{
			
		}
		
		void SetStatusRetire()
		{
			if (m_pAdapter)
				m_pAdapter->SetStatusFlags(2);
		}

		CSetAdapter* GetAdapter() const
		{
			return m_pAdapter;
		}

		void TerminateImmediately()
		{
			if (m_pSetObjectManager)
				m_pSetObjectManager->RemoveListener(this);

			Kill();
		}

		void Deactivate()
		{
			xgame::MsgDeactivate msg{};
			SendMessage(msg);
		}
	};
}
