#pragma once

namespace app::fnd
{
	class RefByHandleObject;
	
	class HandleManagerBase : ReferencedObject
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpHandleManagerBaseAddObject, ASLR(0x00499B80), HandleManagerBase* This, RefByHandleObject& object);

		void AddObject(RefByHandleObject& object)
		{
			ms_fpHandleManagerBaseAddObject(this, object);
		}
	};
}