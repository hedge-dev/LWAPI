#pragma once

namespace app
{
	class CSetAdapter;
	
	class CSetObjectListener : public GameObject3D
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetStatusTemporaryRetire, ASLR(0x008447B0), CSetObjectListener*, float);

	public:
		enum EExtUserDataType
		{
			eExtUserDataType_High, eExtUserDataType_Low
		};

	protected:
		CSetObjectManager* m_pSetObjectManager{};
		CSetAdapter* m_pAdapter{};
		CMyActivationHandle m_ActivationHandle{};

	public:
		csl::ut::LinkListNode ListNode;
		
	public:
		CSetObjectListener()
		{
			ASSERT_OFFSETOF(CSetObjectListener, m_ActivationHandle, 816);
			ASSERT_OFFSETOF(CSetObjectListener, ListNode, 912);

			m_ActivationHandle.SetOwner(this);
		}

		~CSetObjectListener()
		{
			if (m_pSetObjectManager)
				m_pSetObjectManager->RemoveListener(this);
		}
		
	protected:
		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			if (in_rMessage.IsOfType<SetEd::MsgUpdateSetEditor>() || in_rMessage.IsOfType<SetEd::MsgSetObjectEdited>())
			{
				return true;
			}

			return GameObject3D::ProcessMessage(in_rMessage);
		}
		
		virtual void OnInitializedSetObject()
		{
			
		}
		
		virtual void OnPutSetObject(CSetAdapter& in_rAdapter)
		{
			
		}
		
		virtual void OnSetEditorParamChanged(CSetAdapter& in_rAdapter)
		{

		}

	public:
		uint GetExtUserData(EExtUserDataType in_type) const
		{
			if (m_pAdapter)
				return m_pAdapter->GetUserData(in_type);

			return 0;
		}

		void SetExtUserData(EExtUserDataType in_type, uint in_value)
		{
			if (m_pAdapter)
				m_pAdapter->SetUserData(in_type, in_value);
		}

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
		
		virtual void SetAppearance(float in_opacity) // not sure if this is opacity
		{
			
		}
		
		void SetStatusTemporaryRetire(float in_retireTime)
		{
			ms_fpSetStatusTemporaryRetire(this, in_retireTime);
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

		CSetObjectListener* GetParentObject()
		{
			if (!m_pAdapter)
				return { nullptr };
		
			if (!m_pSetObjectManager)
				return { nullptr };

			ut::RefPtr<CSetObject> setObj{};
			m_pSetObjectManager->GetSetObjectFromUniqID(setObj, m_pAdapter->GetObjectResource().GetParentID());
			if (!setObj)
				return { nullptr };
		
			return setObj->GetNthObject(0);
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
