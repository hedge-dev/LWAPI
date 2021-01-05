#pragma once

// C Standard Library
#include "cslib/utilities/Bitset.h"
#include "cslib/utilities/utils.h"
#include "cslib/math/math.h"
#include "cslib/foundation/IAllocator.h"
#include "cslib/utilities/collections/MoveArray.h"
#include "cslib/utilities/collections/InplaceMoveArray.h"
#include "cslib/utilities/collections/ObjectMoveArray.h"
#include "cslib/utilities/collections/LinkList.h"
#include "cslib/foundation/Singleton.h"

// Hedgehog Library
#include "Hedgehog/Base/System/hhAllocator.h"
#include "Hedgehog/Base/System/hhBaseObject.h"
#include "Hedgehog/Base/System/hhReferencedObject.h"
#include "Hedgehog/Base/System/hhRefCountObject.h"
#include "Hedgehog/Base/System/hhHandleManagerBase.h"
#include "Hedgehog/Base/System/hhProperty.h"

// Hedgehog Universe Library
#include "Hedgehog/Base/Universe/hhMessage.h"
#include "Hedgehog/Base/Universe/hhMessageManager.h"
#include "Hedgehog/Base/Universe/hhActor.h"
#include "Hedgehog/Base/Universe/hhLeafActor.h"

#include "Hedgehog/Pack/System/hhPackFile.h"
#include "Hedgehog/Graphics/hhModel.h"

// System
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