#pragma once

namespace app::gfx
{
	class RenderableContainer : public fnd::ReferencedObject
	{
	public:
		csl::ut::LinkList<Renderable> Renderables{ &Renderable::ListNode };

		void AddObject(Renderable* in_pObj)
		{
			Renderables.push_back(in_pObj);
		}

		void RemoveObject(Renderable* in_pObj)
		{
			Renderables.erase(in_pObj);
		}
	};
}