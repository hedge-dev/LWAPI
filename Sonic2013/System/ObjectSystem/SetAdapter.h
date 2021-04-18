#pragma once

namespace app
{
	class CSetObjectListener;
	class CSetAdapterMgr;
	
	class CSetAdapter
	{
	protected:
		CSetAdapterMgr* m_pAdapterManager;
		CSetObjectListener* m_pListener;
		SetEd::CResObject m_pObject;
		Gops::CActor* m_pActor;
		uint m_StatusFlags;
		float m_RetireTime;
		
	public:
		CSetObjectListener* GetListener() const
		{
			return m_pListener;
		}
		
		void SetListener(CSetObjectListener* pListener)
		{
			m_pListener = pListener;
		}

		uint GetStatusFlags() const
		{
			return m_StatusFlags;
		}
		
		void SetStatusFlags(uint flag)
		{
			m_StatusFlags |= flag;
		}

		const SetEd::CResObject& GetObjectResource() const
		{
			return m_pObject;
		}

		Gops::CActor* GetActor() const
		{
			return m_pActor;
		}

		const char* GetName() const
		{
			return m_pObject.GetName();
		}

		void* GetData() const
		{
			if (m_pObject.IsValid())
				return m_pObject.GetParamAddress();
			
			return nullptr;
		}

		const csl::math::Vector3& GetPosition(size_t unit) const
		{
			return m_pObject.GetUnit(unit).GetPosition();
		}
		
		static CSetAdapter* GetPointerFromActor(const Gops::CActor& pActor)
		{
			return pActor.GetAdapter();
		}
	};
}