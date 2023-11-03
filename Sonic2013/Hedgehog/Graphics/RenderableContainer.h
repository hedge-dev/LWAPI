#pragma once

namespace app::gfx
{
	class RenderableContainer : public fnd::ReferencedObject
	{
	public:
		csl::ut::LinkList<Renderable> m_Renderables{ &Renderable::m_ListNode };

		void AddObject(Renderable* in_pObj)
		{
			m_Renderables.push_back(in_pObj);
		}

		void RemoveObject(Renderable* in_pObj)
		{
			m_Renderables.erase(in_pObj);
		}
	};
}