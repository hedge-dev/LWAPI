#pragma once

namespace app::fnd
{
	class FileReader;
	class FileBinder;
	class FileHandleObj : public ThreadSafeReferencedObject
	{
		friend FileReader;
		friend FileBinder;

	public:
		void* m_pBuffer{};
		size_t m_BufferSize{};
		size_t m_Size{};
		size_t m_Status{};
		csl::ut::FixedString<64> m_Path{};
		csl::ut::FixedString<48> m_Name{};
		FileBinder* m_pBinder{};
		void* m_Unk1{};
		csl::fnd::IAllocator* m_pBufferAllocator{};
		size_t m_BufferFlags{};

		void Destroy()
		{
			if (!IsValid())
				return;

			if (!(m_BufferFlags & 1) && m_pBufferAllocator)
				m_pBufferAllocator->Free(m_pBuffer);

			m_pBuffer == nullptr;
			m_pBinder = nullptr;
			m_Unk1 = nullptr;
			m_BufferSize = 0;
			m_Size = 0;
			m_Status = 0;
			m_Path[0] = 0;
			m_Name[0] = 0;
		}
	
	public:
		FileHandleObj()
		{
			
		}

		~FileHandleObj()
		{
			Destroy();
		}

	public:
		bool IsValid() const
		{
			return m_Status != 0;
		}
	};

	namespace file
	{
		inline static FileHandleObj* CreateHandle(csl::fnd::IAllocator* pAlloc)
		{
			return new(pAlloc) FileHandleObj();
		}
	}
}