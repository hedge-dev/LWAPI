#pragma once

namespace app::fnd
{
	class RefByHandleObject;
	
	class HandleManagerBase : public ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddObject, ASLR(0x00499B80), HandleManagerBase*, RefByHandleObject&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveObject, ASLR(0x00499BD0), HandleManagerBase*, RefByHandleObject&);

	public:
		void AddObject(RefByHandleObject& in_rObject)
		{
			ms_fpAddObject(this, in_rObject);
		}

		void RemoveObject(RefByHandleObject& in_rObject)
		{
			ms_fpRemoveObject(this, in_rObject);
		}
	};
}