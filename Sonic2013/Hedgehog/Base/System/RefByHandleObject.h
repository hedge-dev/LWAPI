#pragma once

namespace app::fnd
{
	class RefByHandleObject;
	
	struct HandleTableEntry
	{
		size_t Handle{};
		RefByHandleObject* pObject{};
	};

	class HandleBase;
	
	class RefByHandleObject : public ReferencedObject
	{
		friend HandleBase;
		
	protected:
		size_t m_Handle{};
		HandleTableEntry* m_pHandleEntry{};

	public:
		~RefByHandleObject() override
		{
			
		}
		
		RefByHandleObject()
		{
			
		}
	};
}