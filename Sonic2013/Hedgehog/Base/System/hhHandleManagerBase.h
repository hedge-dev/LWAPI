#pragma once

namespace app::fnd
{
	class RefByHandleObject;
	
	class HandleManagerBase : public ReferencedObject
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddObject, ASLR(0x00499B80), HandleManagerBase* This, RefByHandleObject& object);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveObject, ASLR(0x00499BD0), HandleManagerBase* This, RefByHandleObject& object);

		void AddObject(RefByHandleObject& object)
		{
			ms_fpAddObject(this, object);
		}

		void RemoveObject(RefByHandleObject& object)
		{
			ms_fpRemoveObject(this, object);
		}
	};
}