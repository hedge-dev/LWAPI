#pragma once

namespace app
{
	class CSetObjectListener;
	class CSetObjectManager;
	
	class CSetObject : public hh::base::CRefCountObject
	{
	public:
		inline static FUNCTION_PTR(CSetObjectListener*, __thiscall, ms_fpGetNthObject, ASLR(0x00841400), const CSetObject*, size_t);
		
		CSetObjectManager* m_pManager;
		Gops::CActorPack* m_pPack{};
		void* m_pUnk2{};
		
		CSetObject()
		{
			
		}

		CSetObjectListener* GetNthObject(size_t n)
		{
			for (auto actor : m_pPack->GetActors())
			{
				if (actor.GetUnitNum() == n)
					return CSetAdapter::GetPointerFromActor(actor)->GetListener();
			}
			
			return nullptr;
		}
	};
}