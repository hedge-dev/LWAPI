#pragma once

namespace app::fnd
{
	class FileReader;
	class FileBinder;

	enum EFileStatus : uint32_t
	{
		eFileStatus_Invalid,
		eFileStatus_None,
		eFileStatus_Request,
		eFileStatus_Loading,
		eFileStatus_Complete,
		eFileStatus_Error,
		eFileStatus_Stop,
	};

	class FileHandleObj : public ThreadSafeReferencedObject
	{
		friend FileReader;
		friend FileBinder;

	public:
		void* pBuffer{};
		size_t BufferSize{};
		size_t Size{};
		EFileStatus Status{};
		csl::ut::FixedString<64> Path{};
		csl::ut::FixedString<48> Name{};
		FileBinder* pBinder{};
		void* pTag{};
		csl::fnd::IAllocator* pBufferAllocator{};
		size_t BufferFlags{};

		void Destroy()
		{
			if (!IsValid())
				return;

			if (!(BufferFlags & 1) && pBufferAllocator)
				pBufferAllocator->Free(pBuffer);

			pBuffer == nullptr;
			pBinder = nullptr;
			pTag = nullptr;
			BufferSize = 0;
			Size = 0;
			Status = eFileStatus_None;
			Path[0] = 0;
			Name[0] = 0;
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
			return Status != 0;
		}
	};

	namespace file
	{
		inline static FileHandleObj* CreateHandle(csl::fnd::IAllocator* in_pAlloc)
		{
			return new(in_pAlloc) FileHandleObj();
		}
	}
}