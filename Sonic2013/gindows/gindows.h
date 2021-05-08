#pragma once

namespace gindows
{
	inline static csl::fnd::IAllocator** ms_ppGindowsAllocator = reinterpret_cast<csl::fnd::IAllocator**>(ASLR(0x00FF00A8));

	static csl::fnd::IAllocator* GetMemoryAllocator()
	{
		return *ms_ppGindowsAllocator;
	}

	static void SetMemoryAllocator(csl::fnd::IAllocator* pAllocator)
	{
		*ms_ppGindowsAllocator = pAllocator;
	}

	class DelegateAllocator
	{
	public:
		void* Alloc(size_t size, int alignment)
		{
			return GetMemoryAllocator()->Alloc(size, alignment);
		}

		void Free(void* loc)
		{
			return GetMemoryAllocator()->Free(loc);
		}
	};
	
	// One day
	typedef uint PrimType;
	typedef uint IconKind;
	typedef uint MouseCursorType;
	typedef void PrimitiveVertex;
}

#include "Allocator.h"
#include "Object.h"

#include "Device/RenderState.h"
#include "Device/RenderBase.h"
#include "Device/RenderDevice.h"
#include "Device/Font.h"
#include "Device/Graphics.h"

#include "Pad.h"
#include "Mouse.h"
#include "Keys.h"
#include "Keyboard.h"
#include "KeyboardPad.h"

#include "EventArgs.h"
#include "Canvas.h"
#include "Control.h"
#include "Form.h"
#include "Desktop.h"
#include "Manager.h"


// Include code
#include "Control.inl"