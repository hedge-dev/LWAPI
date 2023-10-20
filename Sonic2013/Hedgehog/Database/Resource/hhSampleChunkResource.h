#pragma once

namespace hh::db
{
	class CSampleChunkResource2
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResolvePointer, ASLR(0x00C27CB0), CSampleChunkResource2*);

	public:
		void ResolvePointer()
		{
			ms_fpResolvePointer(this);
		}
	};
}