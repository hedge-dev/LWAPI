#pragma once

namespace app::fnd
{
	class IOStream : public fnd::ReferencedObject
	{
	protected:
		bool m_Unk1{};
		
	public:
		typedef void Callback(int, IOStream* pStream, void* pBuffer);
		
		virtual void Close() = 0;
		virtual size_t Read(void* pBuffer, size_t bufSize) { return 0; }
		virtual size_t ReadAsync(void* pBuffer, size_t bufSize, Callback* pCallback, void*) { return 0; }
		virtual size_t Write(const void* pBuffer, size_t bufSize) { return 0; }
		virtual size_t WriteAsync(void* pBuffer, size_t bufSize, Callback* pCallback, void*) { return 0; }

		virtual bool WaitAsync() const
		{
			while (IsBusy())
				;

			return m_Unk1;
		}
		
		virtual bool IsBusy() const { return false; }
		virtual bool CanAsync() const = 0;
		virtual bool CanRead() const = 0;
		virtual bool CanWrite() const = 0;
		virtual bool IsAvailable() const = 0;
		virtual size_t GetSize() const = 0;
		
		virtual size_t GetOffsetAlign() { return 1; }
		virtual size_t GetSizeAlign() { return 1; }
		virtual size_t GetBufferAlign() { return 1; }
	};
}