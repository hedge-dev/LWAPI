#pragma once
#include "Control.h"

namespace gindows
{
	// Form : ScrollableContent
	class Form : public Control
	{
	protected:
		csl::ut::Bitset<uint> m_FormFlags;
		INSERT_PADDING(36){};
		
	public:
		csl::ut::LinkListNode m_FormsNode{nullptr, nullptr};
		csl::ut::LinkListNode m_ActiveFormsNode{nullptr, nullptr};
		void* m_Unk1{};
		
		Form()
		{
			
		}
	};
}