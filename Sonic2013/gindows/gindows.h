#pragma once

namespace gindows
{
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