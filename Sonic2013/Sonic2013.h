#pragma once

// Common Sonicteam Library
#include "Sonicteam/utilities/Bitset.h"
#include "Sonicteam/utilities/Enum.h"
#include "Sonicteam/utilities/utils.h"
#include "Sonicteam/utilities/NonCopyable.h"
#include "Sonicteam/utilities/detail/RuntimeTypeInfo.h"
#include "Sonicteam/math/math.h"
#include "Sonicteam/System/Mutex.h"
#include "Sonicteam/System/IAllocator.h"
#include "Sonicteam/System/Singleton.h"
#include "Sonicteam/utilities/collections/Array.h"
#include "Sonicteam/utilities/collections/MoveArray.h"
#include "Sonicteam/utilities/collections/InplaceMoveArray.h"
#include "Sonicteam/utilities/collections/ObjectMoveArray.h"
#include "Sonicteam/utilities/collections/LinkList.h"
#include "Sonicteam/utilities/VariableString.h"
#include "Sonicteam/utilities/Point.h"
#include "Sonicteam/utilities/Size.h"
#include "Sonicteam/utilities/Rectangle.h"
#include "Sonicteam/utilities/Color.h"

// Dummy standard library
#include "std-dummy/std-dummy.h"

// gindows
#include "gindows/gindows.h"

// Hedgehog Library
#include "Hedgehog/Base/System/hhAllocator.h"
#include "Hedgehog/Base/System/hhBaseObject.h"
#include "Hedgehog/Base/System/hhReferencedObject.h"
#include "Hedgehog/Base/System/hhRefCountObject.h"
#include "Hedgehog/Base/System/hhHandleManagerBase.h"
#include "Hedgehog/Base/System/hhProperty.h"
#include "Hedgehog/Base/System/hhSyncTimer.h"
#include "Hedgehog/Base/System/hhDevicePlatformBase.h"
#include "Hedgehog/Base/System/hhDeviceBase.h"
#include "Hedgehog/Base/System/hhApplication.h"
#include "System/GlobalAllocator.h"

// Hedgehog Utility Library
#include "Hedgehog/Base/Utility/hhScopedPointer.h"

// Hedgehog Universe Library
#include "Hedgehog/Base/Universe/hhMessage.h"
#include "Hedgehog/Base/Universe/hhMessageManager.h"
#include "Hedgehog/Base/Universe/hhActor.h"
#include "Hedgehog/Base/Universe/hhLeafActor.h"
#include "Hedgehog/Base/Universe/hhBranchActor.h"

// Hedgehog Reflection Library
#include "Hedgehog/Reflection/hhRflCustomAttribute.h"
#include "Hedgehog/Reflection/hhRflClassMember.h"
#include "Hedgehog/Reflection/hhRflClassEnum.h"
#include "Hedgehog/Reflection/hhRflClass.h"

#include "Hedgehog/Pack/System/hhPackFile.h"
#include "Hedgehog/Graphics/hhModel.h"

// System
#include "System/Singleton.h"
#include "System/ApplicationWin.h"
#include "System/DeviceWin.h"
#include "System/GameDocument.h"
#include "System/ObjectSystem/GameObjectSystem.h"
#include "Hedgehog/Base/System/hhRefByHandleObject.h"
#include "System/Messages.h"
#include "System/GOComponent.h"
#include "System/GameObject.h"
#include "System/ObjectSystem/SetAdapter.h"
#include "System/GameService.h"
#include "System/ObjInfo.h"

// System Font
#include "System/Font/Font.h"
#include "System/Font/FontText.h"
#include "System/Font/FontManager.h"

// System Debug
#include "System/Debug/Object.h"
#include "System/Debug/Menu/MenuItem.h"
#include "System/Debug/Menu/Menu.h"
#include "System/Debug/Menu/MenuManager.h"

// Components
#include "System/goc/goc_Transform.h"
#include "System/goc/goc_Visual.h"
#include "System/goc/goc_VisualModel.h"
#include "System/goc/goc_EnemyTarget.h"

// Services
#include "System/Services/service_ObjInfoContainer.h"
#include "System/Services/service_LevelInfo.h"
#include "System/Services/service_GameServiceTypeRegistry.h"

// Objects
#include "System/GameObject3D.h"

// SetData
#include "System/SetObject/SetObjectListener.h"