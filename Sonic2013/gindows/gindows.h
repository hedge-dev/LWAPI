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
	
	// One day
	typedef uint PrimType;
	typedef uint IconKind;
	typedef uint MouseCursorType;
	typedef void PrimitiveVertex;
	typedef void Control;
	typedef void Desktop;
}

#include "Object.h"

#include "Device/RenderState.h"
#include "Device/RenderBase.h"
#include "Device/RenderDevice.h"
#include "Device/DeviceMouse.h"
#include "Device/Font.h"
#include "Device/Graphics.h"

#include "WindowManager.h"
#include "ManagerImpl.h"
#include "Manager.h"