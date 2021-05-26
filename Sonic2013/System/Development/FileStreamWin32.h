#pragma once
#define FILE_FLAG_OPEN 1
#define FILE_FLAG_CREATE 2
#define FILE_FLAG_OPEN_WRITE (FILE_FLAG_OPEN | FILE_FLAG_CREATE)

namespace app::dev
{
	class FileStreamWin32 : public fnd::IOStream
	{
	protected:
		INSERT_PADDING(8){};
		HANDLE m_FileHandle{ INVALID_HANDLE_VALUE };
		uint m_Flags{};
		
	public:
		FileStreamWin32(const char* pFileName, uint flags)
		{
			Open(pFileName, flags);
		}

		~FileStreamWin32()
		{
			FileStreamWin32::Close();
		}
		
		void Close() override final
		{
			if (!FileStreamWin32::IsAvailable())
				return;

			CloseHandle(m_FileHandle);
			m_FileHandle = (HANDLE)-1;
			m_Flags = 0;
		}
		
		size_t Read(void* pBuffer, size_t bufSize) override final
		{
			if (!IsAvailable())
				return 0;
			
			DWORD bytesRead = 0;
			bool success = ReadFile(m_FileHandle, pBuffer, bufSize, &bytesRead, NULL);
			return success ? bytesRead : 0;
		}

		size_t Write(const void* pBuffer, size_t bufSize) override final
		{
			if (!IsAvailable())
				return 0;

			DWORD bytesWritten = 0;
			bool success = WriteFile(m_FileHandle, pBuffer, bufSize, &bytesWritten, NULL);
			return success ? bytesWritten : 0;
		}
		
		bool CanRead() const override final
		{
			if (!IsAvailable())
				return false;
			
			return m_Flags & FILE_FLAG_OPEN;
		}

		bool CanWrite() const override final
		{
			if (!IsAvailable())
				return false;

			return m_Flags & FILE_FLAG_CREATE;
		}

		size_t GetSize() const override
		{
			if (!IsAvailable())
				return 0;

			return GetFileSize(m_FileHandle, 0);
		}
		
		HH_FORCE_INLINE bool IsAvailable() const override final
		{
			return m_FileHandle != INVALID_HANDLE_VALUE;
		}

	protected:
		void Open(const char* pName, uint flags)
		{
			DWORD accessFlags = 0;
			DWORD creationDisposition = 0;

			if (flags & FILE_FLAG_OPEN_WRITE == FILE_FLAG_OPEN_WRITE)
			{
				accessFlags = GENERIC_READ | GENERIC_WRITE;
				creationDisposition = OPEN_ALWAYS;
			}
			else if (flags & FILE_FLAG_OPEN)
			{
				accessFlags |= GENERIC_READ;
				creationDisposition = OPEN_EXISTING;
			}
			else if (flags & FILE_FLAG_CREATE)
			{
				accessFlags |= GENERIC_WRITE;
				creationDisposition = CREATE_ALWAYS;
			}
			else
				creationDisposition = flags;
			
			HANDLE handle = CreateFileA(pName, accessFlags, 0, NULL, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
			m_FileHandle = handle;
			if (handle != INVALID_HANDLE_VALUE)
				m_Flags = flags;
		}
	};
}