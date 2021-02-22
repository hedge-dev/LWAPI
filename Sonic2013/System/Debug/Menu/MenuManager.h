#pragma once

namespace app::dbg
{
	class MenuManager : public fnd::ReferencedObject, csl::fnd::SingletonPointer<MenuManager>
	{
	protected:
		uint m_State;
		Menu* m_pRoot;
		Menu* m_pSelected;
		void* m_Unk1;

	public:
		Menu* GetRootMenu() const 
		{
			return m_pRoot;
		}

		Menu* GetSelectedMenu() const 
		{
			return m_pSelected;
		}
	};
}

DEFINE_SINGLETONPTR(app::dbg::MenuManager, ASLR(0x00FD4048));