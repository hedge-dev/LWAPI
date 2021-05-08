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

		DataValue(void* pData, const RflClassMember* pMember)
		{
			m_pData = pData;
			m_pMember = pMember;
		}

		DataValue(void* pInst, const RflClass* pClass, const char* pMemberName)
		{
			m_pMember = pClass->GetMemberByName(pMemberName);
			if (m_pMember)
				m_pData = reinterpret_cast<void*>(reinterpret_cast<size_t>(pInst) + m_pMember->GetByteOffset());
		}
	};
}