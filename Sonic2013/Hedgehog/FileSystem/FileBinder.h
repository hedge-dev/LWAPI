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
		virtual size_t BindCpk(const char* in_pName, int in_priority, bool in_a3) { return 0; }
		virtual size_t BindDirectory(const char* in_pName, int in_priority, bool in_a3) { return 0; }
		virtual size_t BindFile(const char* in_pName, int in_priority, bool a3) { return 0; }
		virtual bool IsSyncComplete(size_t in_id) { return false; }
		virtual bool IsSyncCompleteAll() { return false; }
		virtual void WaitSync(size_t in_id) {  }
		virtual void WaitSyncAll() {  }
		virtual void SetCurrentDirectory(size_t in_id, const char* in_pDir) {  }
		virtual void Unbind(size_t in_id) {  }
		virtual void UnbindAll() {  }
		virtual bool IsFileExist(const char* in_pFile) { return false; }
		virtual size_t GetFileSize(const char* in_pFile) { return 0; }
		virtual bool IsBind(uint in_index) const
		{
			return false;
		}
	};
}

#pragma pop_macro("SetCurrentDirectory")