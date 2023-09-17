#pragma once

namespace app
{
	class AocManager : public fnd::ReferencedObject, public csl::fnd::SingletonPointer<AocManager>
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpTitleListUpAsync, ASLR(0x004B0900), AocManager*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsTitleEnumerationComplete, ASLR(0x004B0560), const AocManager*);
		inline static FUNCTION_PTR(int, __thiscall, ms_fpGetNumTitles, ASLR(0x004B0570), const AocManager*);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpOpenTitle, ASLR(0x004B0910), AocManager*, int);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCloseTitle, ASLR(0x004B0580), AocManager*, void*);
		inline static FUNCTION_PTR(const char*, __thiscall, ms_fpGetContentPath, ASLR(0x004B05C0), const AocManager*, void*);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpGetPurchaseInfo, ASLR(0x004B0920), AocManager*, void*, bool*, ushort*, uint);

	public:
		INSERT_PADDING(4); // AocManagerImpl

		void TitleListUpAsync()
		{
			ms_fpTitleListUpAsync(this);
		}

		bool IsTitleEnumerationComplete() const
		{
			return ms_fpIsTitleEnumerationComplete(this);
		}

		int GetNumTitles() const
		{
			return ms_fpGetNumTitles(this);
		}

		void* OpenTitle(int in_index)
		{
			return ms_fpOpenTitle(this, in_index);
		}

		void CloseTitle(void* in_pTitle)
		{
			ms_fpCloseTitle(this, in_pTitle);
		}

		const char* GetContentPath(void* in_pTitle) const
		{
			return ms_fpGetContentPath(this, in_pTitle);
		}

		void* GetPurchaseInfo(void* in_pTitle, bool* out_pIsPurchased, ushort* in_pDlcIndex, uint count)
		{
			return ms_fpGetPurchaseInfo(this, in_pTitle, out_pIsPurchased, in_pDlcIndex, count);
		}
	};
}

DEFINE_SINGLETONPTR(app::AocManager, ASLR(0x00FD733C));