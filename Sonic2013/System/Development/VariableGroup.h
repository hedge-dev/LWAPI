#pragma once

namespace app::dev
{
	class S13VariableGroup : public S13Variable
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x0045A750), S13VariableGroup*, const char*);

	public:
		INSERT_PADDING(12){};
		void* Unk1;
		
		inline static S13VariableGroup* Create(const char* in_pName)
		{
			auto* pGroup = reinterpret_cast<S13VariableGroup*>(operator new(sizeof(S13VariableGroup)));
			ms_fpCtor(pGroup, in_pName);
			return pGroup;
		}
	};
}