#pragma once

namespace app::fnd
{
	template<typename T>
	class ResCommon
	{
	protected:
		T* m_pRes{};

	public:
		ResCommon(T* pRes) : m_pRes(pRes)
		{

		}

		bool IsValid() const
		{
			return m_pRes != nullptr;
		}

		T* operator->() const
		{
			return m_pRes;
		}

		T& operator*() const
		{
			return *m_pRes;
		}

		operator T*() const
		{
			return m_pRes;
		}
		
		const T& ref() const
		{
			return *m_pRes;
		}

		T& ref()
		{
			return *m_pRes;
		}
	};

	class ResRawData
	{
		const char* m_pName{};
		void* m_pData{};
		void* m_pAddress{};
		size_t m_DataSize{};
		size_t m_pUnk1{}; // Alignment?

	public:
		const char* GetName() const
		{
			return m_pName;
		}

		void* GetData() const
		{
			return m_pData;
		}

		void* GetAddress() const
		{
			return m_pAddress;
		}

		size_t GetSize() const
		{
			return m_DataSize;
		}
	};
}