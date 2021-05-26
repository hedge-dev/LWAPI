#pragma once

namespace app::dev
{
	class CReflectionEditWindow : public dbg::FormObject
	{
	public:
		CReflectionEditControl* m_pEditor;
		
		CReflectionEditWindow() : FormObject("Reflection Edit Window")
		{
			m_pEditor = new CReflectionEditControl(nullptr);
			if (m_pEditor)
				Control::Add(m_pEditor);
			
			csl::ut::Point2<int> location{ 300, 100 };
			csl::ut::Size2<int> size{ 480, 320 };
			
			SetSize(size);
			SetLocation(location);
			
			SetFont(0);
			SetFocus();
			Reset();
		}

		void Setup(fnd::DataResource* pResource)
		{
			if (m_pEditor)
				m_pEditor->Setup(pResource);
		}

		void Reset()
		{
			if (m_pEditor)
				m_pEditor->Reset();
		}

		void OnKeyDown(gindows::KeyEventArgs& args) override
		{
			if (!args.m_Handled)
			{
				// ???, it just does that
				args.m_ProcessCount++;
				m_pEditor->OnKeyDown(args);
				args.m_ProcessCount--;
			}

			FormObject::OnKeyDown(args);
		}

		static CReflectionEditWindow* Create(fnd::DataResource* pResource)
		{
			FUNCTION_PTR(void, __thiscall, fp_ReflectionEditWindowCtor, ASLR(0x00459220), CReflectionEditWindow*);
			FUNCTION_PTR(void, __thiscall, fp_ReflectionEditWindowSetup, ASLR(0x00459190), CReflectionEditWindow*, fnd::DataResource*);

			//auto* pWindow = reinterpret_cast<CReflectionEditWindow*>(operator new(sizeof(CReflectionEditWindow)));
			//fp_ReflectionEditWindowCtor(pWindow);

			//if (pWindow)
			//	fp_ReflectionEditWindowSetup(pWindow, pResource);
			
			auto* pWindow = new CReflectionEditWindow();

			if (pWindow)
				pWindow->Setup(pResource);

			return pWindow;
		}
	};
}