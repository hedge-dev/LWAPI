#pragma once

namespace app::dev
{
	class S13VariableGroup : public S13Variable
	{
	public:
		INSERT_PADDING(12){};
		void* m_Unk1;

		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x0045A750), S13VariableGroup* pThis, const char* pName);
		
		inline static S13VariableGroup* Create(const char* pName)
		{
			auto* pGroup = reinterpret_cast<S13VariableGroup*>(operator new(sizeof(S13VariableGroup)));
			ms_fpCtor(pGroup, pName);
			return pGroup;
		}
	};
}