#pragma once

namespace app::fnd
{
	class IOStream;
	
	class RflSerializeUtil
	{
	protected:
		inline static FUNCTION_PTR(bool, __cdecl, ms_fpSave, ASLR(0x0049FED0), const void* pData, const RflClass* pClass, IOStream* pOutStream, bool encrypt);
		inline static FUNCTION_PTR(DataResource*, __cdecl, ms_fpLoad, ASLR(0x0049FF50), IOStream* pInStream, csl::fnd::IAllocator* pAllocator, bool encrypted);
		
	public:
		static bool Save(Variant data, IOStream* pOutStream, bool encrypt = false)
		{
			return ms_fpSave(data.m_pObject, data.m_pClass, pOutStream, encrypt);
		}

		static DataResource* Load(IOStream* pInStream, csl::fnd::IAllocator* pAllocator, bool encrypted = false)
		{
			return ms_fpLoad(pInStream, pAllocator, encrypted);
		}
	};
}