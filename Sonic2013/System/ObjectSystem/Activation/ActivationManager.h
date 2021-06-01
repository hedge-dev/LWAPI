#pragma once

namespace app
{
	class CActivationManager : public fnd::GameService	
	{
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEF2C8));
		
	protected:
		csl::ut::LinkList<CActivationHandle> m_Handles{};
		csl::ut::LinkList<CActivationVolume> m_Volumes{ &CActivationVolume::m_ListNode };
		
	public:
		CActivationManager() : GameService(0)
		{
			
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
		
		void AddVolume(CActivationVolume* pVolume)
		{
			m_Volumes.push_back(pVolume);
			pVolume->m_pManager = this;
		}

		void RemoveVolume(CActivationVolume* pVolume)
		{
			m_Volumes.erase(pVolume);
			pVolume->m_pManager = nullptr;
		}

		const csl::ut::LinkList<CActivationVolume>& GetVolumes() const
		{
			return m_Volumes;
		}
	};
}
