#pragma once

namespace app::dev
{
	class CReflectionEditWindow : public dbg::FormObject
	{
	public:
		CReflectionEditControl* pEditor;
		
		CReflectionEditWindow() : FormObject("Reflection Edit Window")
		{
			pEditor = new CReflectionEditControl(nullptr);
			if (pEditor)
				Control::Add(pEditor);
			
			csl::ut::Point2<int> location{ 300, 100 };
			csl::ut::Size2<int> size{ 480, 320 };
			
			SetSize(size);
			SetLocation(location);
			
			SetFont(0);
			SetFocus();
			Reset();
		}

		void Setup(fnd::DataResource* in_pResource)
		{
			if (pEditor)
				pEditor->Setup(in_pResource);
		}

		void Reset()
		{
			if (pEditor)
				pEditor->Reset();
		}

		void OnKeyDown(gindows::KeyEventArgs& in_rArgs) override
		{
			if (!in_rArgs.Handled)
			{
				// ???, it just does that
				in_rArgs.ProcessCount++;
				pEditor->OnKeyDown(in_rArgs);
				in_rArgs.ProcessCount--;
			}

			FormObject::OnKeyDown(in_rArgs);
		}

		static CReflectionEditWindow* Create(fnd::DataResource* in_pResource)
		{
			FUNCTION_PTR(void, __thiscall, fpReflectionEditWindowCtor, ASLR(0x00459220), CReflectionEditWindow*);
			FUNCTION_PTR(void, __thiscall, fpReflectionEditWindowSetup, ASLR(0x00459190), CReflectionEditWindow*, fnd::DataResource*);

			//auto* pWindow = reinterpret_cast<CReflectionEditWindow*>(operator new(sizeof(CReflectionEditWindow)));
			//fpReflectionEditWindowCtor(pWindow);

			//if (pWindow)
			//	fpReflectionEditWindowSetup(pWindow, pResource);
			
			auto* pWindow = new CReflectionEditWindow();

			if (pWindow)
				pWindow->Setup(in_pResource);

			return pWindow;
		}
	};
}