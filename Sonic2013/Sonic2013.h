#pragma once

// C Standard Library
#include "cslib/utilities/Bitset.h"
#include "cslib/utilities/Enum.h"
#include "cslib/utilities/utils.h"
#include "cslib/utilities/detail/RuntimeTypeInfo.h"
#include "cslib/math/math.h"
#include "cslib/foundation/IAllocator.h"
#include "cslib/utilities/collections/Array.h"
#include "cslib/utilities/collections/MoveArray.h"
#include "cslib/utilities/collections/InplaceMoveArray.h"
#include "cslib/utilities/collections/ObjectMoveArray.h"
#include "cslib/utilities/collections/LinkList.h"
#include "cslib/utilities/VariableString.h"
#include "cslib/foundation/Singleton.h"

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