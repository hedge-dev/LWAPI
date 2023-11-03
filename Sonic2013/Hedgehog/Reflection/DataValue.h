#pragma once

namespace app::fnd
{
	class DataValue
	{
	protected:
		void* m_pData{};
		const RflClassMember* m_pMember{};

	public:
		DataValue()
		{
			
		}

		DataValue(void* in_pData, const RflClassMember* in_pMember)
		{
			m_pData = in_pData;
			m_pMember = in_pMember;
		}

		DataValue(void* in_pInst, const RflClass* in_pClass, const char* in_pMemberName)
		{
			m_pMember = in_pClass->GetMemberByName(in_pMemberName);
			if (m_pMember)
				m_pData = reinterpret_cast<void*>(reinterpret_cast<size_t>(in_pInst) + m_pMember->GetByteOffset());
		}
	};
}