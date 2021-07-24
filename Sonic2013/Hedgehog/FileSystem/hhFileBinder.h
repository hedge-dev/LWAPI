#pragma once
#pragma push_macro("SetCurrentDirectory")
#undef SetCurrentDirectory

namespace app::fnd
{
	class FileBinder
	{
	public:
		virtual ~FileBinder() = default;
		virtual size_t GetBinderHn() { return 0; };
		virtual size_t BindCpk(const char* pName, int priority, bool a3) { return 0; }
		virtual size_t BindDirectory(const char* pName, int priority, bool a3) { return 0; }
		virtual size_t BindFile(const char* pName, int priority, bool a3) { return 0; }
		virtual bool IsSyncComplete(size_t id) { return false; }
		virtual bool IsSyncCompleteAll() { return false; }
		virtual void WaitSync(size_t id) {  }
		virtual void WaitSyncAll() {  }
		virtual void SetCurrentDirectory(size_t id, const char* pDir) {  }
		virtual void Unbind(size_t id) {  }
		virtual void UnbindAll() {  }
		virtual bool IsFileExist(const char* pFile) { return false; }
		virtual size_t GetFileSize(const char* pFile) { return 0; }
		virtual bool IsBind(const char* pName)
		{
			return false;
		}
	};
}

#pragma pop_macro("SetCurrentDirectory")