#pragma once

// C Standard Library
#include "cslib/utils.h"
#include "cslib/math.h"
#include "cslib/IAllocator.h"
#include "cslib/MoveArray.h"
#include "cslib/LinkList.h"

// Hedgehog Library
#include "Hedgehog/Base/System/hhBaseObject.h"
#include "Hedgehog/Base/System/hhReferencedObject.h"
#include "Hedgehog/Base/System/hhRefCountObject.h"
#include "Hedgehog/Base/System/hhRefByHandleObject.h"
#include "Hedgehog/Base/System/hhProperty.h"

// Hedgehog Universe Library
#include "Hedgehog/Base/Universe/hhMessage.h"
#include "Hedgehog/Base/Universe/hhActor.h"
#include "Hedgehog/Base/Universe/hhLeafActor.h"

// System
#include "System/GameDocument.h"
#include "System/ObjectSystem/GameObjectSystem.h"
#include "System/Messages.h"
#include "System/GOComponent.h"
#include "System/GameObject.h"
#include "System/ObjectSystem/SetObjectListener.h"
#include "System/ObjectSystem/SetAdapter.h"