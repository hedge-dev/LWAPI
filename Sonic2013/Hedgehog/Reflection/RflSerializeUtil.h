#pragma once

namespace app::fnd
{
	class IOStream;
	
	class RflSerializeUtil
	{
	private:
		inline static FUNCTION_PTR(bool, __cdecl, ms_fpSave, ASLR(0x0049FED0), const void*, const RflClass*, IOStream*, bool);
		inline static FUNCTION_PTR(DataResource*, __cdecl, ms_fpLoad, ASLR(0x0049FF50), IOStream*, csl::fnd::IAllocator*, bool);
		
	public:
		static bool Save(Variant in_data, IOStream* in_pOutStream, bool in_encrypt = false)
		{
			return ms_fpSave(in_data.pObject, in_data.pClass, in_pOutStream, in_encrypt);
		}

		static DataResource* Load(IOStream* in_pInStream, csl::fnd::IAllocator* in_pAllocator, bool in_encrypted = false)
		{
			return ms_fpLoad(in_pInStream, in_pAllocator, in_encrypted);
		}
	};
}