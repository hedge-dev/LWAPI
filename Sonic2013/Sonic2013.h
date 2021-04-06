#pragma once

// Common Sonicteam Library
#include "Sonicteam/Utility/Bitset.h"
#include "Sonicteam/Utility/Enum.h"
#include "Sonicteam/Utility/utils.h"
#include "Sonicteam/Utility/NonCopyable.h"
#include "Sonicteam/Utility/Pair.h"
#include "Sonicteam/Utility/detail/RuntimeTypeInfo.h"
#include "Sonicteam/Utility/detail/LinkListImpl.h"
#include "Sonicteam/math/math.h"
#include "Sonicteam/System/Mutex.h"
#include "Sonicteam/System/IAllocator.h"
#include "Sonicteam/System/Singleton.h"
#include "Sonicteam/System/Delegate.h"
#include "Sonicteam/Utility/collections/Array.h"
#include "Sonicteam/Utility/collections/MoveArray.h"
#include "Sonicteam/Utility/collections/InplaceMoveArray.h"
#include "Sonicteam/Utility/collections/ObjectMoveArray.h"
#include "Sonicteam/Utility/collections/InplaceObjectMoveArray.h"
#include "Sonicteam/Utility/collections/FixedArray.h"
#include "Sonicteam/Utility/collections/LinkList.h"
#include "Sonicteam/Utility/collections/HashMap.h"
#include "Sonicteam/Utility/collections/PointerMap.h"
#include "Sonicteam/Utility/collections/StringMap.h"
#include "Sonicteam/Utility/VariableString.h"
#include "Sonicteam/Utility/FixedString.h"
#include "Sonicteam/Utility/Point.h"
#include "Sonicteam/Utility/Size.h"
#include "Sonicteam/Utility/Rectangle.h"
#include "Sonicteam/Utility/Color.h"
#include "Sonicteam/System/ComPtr.h"

// Dummy standard library
#include "std-dummy/std-dummy.h"

// gindows
#include "gindows/gindows.h"

// Hedgehog Library
#include "Hedgehog/Base/System/hhAllocator.h"
#include "Hedgehog/Base/System/hhBaseObject.h"
#include "Hedgehog/Base/System/hhReferencedObject.h"
#include "Hedgehog/Base/System/hhThreadSafeReferencedObject.h"
#include "Hedgehog/Base/System/hhRefCountObject.h"
#include "Hedgehog/Base/System/hhRefByHandleObject.h"
#include "Hedgehog/Base/System/hhHandleManagerBase.h"
#include "Hedgehog/Base/System/hhHandle.h"
#include "Hedgehog/Base/System/hhProperty.h"
#include "Hedgehog/Base/System/hhSyncTimer.h"
#include "Hedgehog/Base/System/hhPadData.h"
#include "Hedgehog/Base/System/hhDevicePlatformBase.h"
#include "Hedgehog/Base/System/hhDeviceBase.h"
#include "Hedgehog/Base/System/hhApplication.h"
#include "Hedgehog/Base/System/hhActivationHandle.h"
#include "Hedgehog/Base/System/hhFrame.h"
#include "System/GlobalAllocator.h"

// Hedgehog Utility Library
#include "Hedgehog/Base/Utility/hhScopedPointer.h"
#include "Hedgehog/Base/Utility/hhReferencePointer.h"

// Hedgehog Universe Library
#include "Hedgehog/Base/Universe/hhMessage.h"
#include "Hedgehog/Base/Universe/hhMessageManager.h"
#include "Hedgehog/Base/Universe/hhActor.h"
#include "Hedgehog/Base/Universe/hhLeafActor.h"
#include "Hedgehog/Base/Universe/hhBranchActor.h"

// Hedgehog Resource Library
#include "Hedgehog/Resource/hhResCommon.h"
#include "Hedgehog/Pack/System/hhPackFileHeader.h"
#include "Hedgehog/Pack/System/hhPackFile.h"
#include "Hedgehog/Resource/hhResourceTypeInfo.h"
#include "Hedgehog/Resource/hhResourceReflections.h"

// Hedgehog Animation Library
#include "Hedgehog/Animation/Base/hhAnimationObject.h"
#include "Hedgehog/Animation/Base/hhAnimationNode.h"
#include "Hedgehog/Animation/Base/hhAnimationClip.h"
#include "Hedgehog/Animation/Base/hhAnimationListener.h"
#include "Hedgehog/Animation/Resource/hhCharAnimScript.h"
#include "Hedgehog/Animation/Base/hhAnimationCallback.h"
#include "Hedgehog/Animation/Resource/hhAnimationResContainer.h"
#include "Hedgehog/Animation/hhAnimationManager.h"
#include "Hedgehog/Animation/hhSkeletonControl.h"
#include "Hedgehog/Animation/hhSkeletonBlender.h"
#include "Hedgehog/Animation/hhComplexBlender.h"
#include "Hedgehog/Animation/hhComplexImpl.h"
#include "Hedgehog/Animation/hhAnimationSimple.h"
#include "Hedgehog/Animation/hhAnimationComplex.h"
#include "Hedgehog/Animation/hhSimpleBlender.h"
#include "Hedgehog/Animation/hhCallbackExecutioner.h"
#include "Hedgehog/Animation/hhAnimationNodeManager.h"
#include "Hedgehog/Animation/hhCharactorAnimation.h"
#include "Hedgehog/Animation/hhCharactorAnimationSingle.h"
#include "Hedgehog/Animation/hhCharactorAnimationMultiLayer.h"

// Hedgehog Reflection Library
#include "Hedgehog/Reflection/hhRflCustomAttribute.h"
#include "Hedgehog/Reflection/hhRflClassMember.h"
#include "Hedgehog/Reflection/hhRflClassEnum.h"
#include "Hedgehog/Reflection/hhRflClass.h"

// System Game
#include "System/Game/LuaScript.h"

// System
#include "System/Singleton.h"
#include "System/ApplicationWin.h"
#include "System/DeviceWin.h"
#include "System/GameSequence.h"
#include "System/Game.h"
#include "System/GameDocument.h"
#include "System/ObjectSystem/GameObjectSystem.h"
#include "System/Messages.h"
#include "System/GOComponent.h"
#include "System/GameObject.h"
#include "System/GameObjectHandle.h"
#include "System/GameService.h"
#include "System/ObjInfo.h"
#include "System/FileLoader.h"
#include "System/ResourceManager.h"
#include "System/DeviceManager.h"

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
#include "System/goc/goc_VisualTransformed.h"
#include "System/goc/goc_VisualModel.h"
#include "System/goc/goc_VisualContainer.h"
#include "System/goc/goc_Collider.h"
#include "System/goc/goc_Animation.h"
#include "System/goc/goc_AnimationSingle.h"
#include "System/goc/goc_AnimationSimple.h"
#include "System/goc/goc_AnimationScript.h"
#include "System/goc/goc_AnimationScriptLayer.h"
#include "System/goc/goc_AnimationContainer.h"
#include "System/goc/goc_EnemyTarget.h"

// Services
#include "System/Services/service_ObjInfoContainer.h"
#include "System/Services/service_LevelInfo.h"
#include "System/Services/service_GameServiceTypeRegistry.h"

// Objects
#include "System/GameObject3D.h"

// SetData
#include "System/SetObject/MyActivationHandle.h"
#include "System/SetObject/Object.h"
#include "System/SetObject/SetAdapter.h"
#include "System/SetObject/SetObjectListener.h"
#include "System/SetObject/service_SetObjectManager.h"

// Stage Data
#include "System/Stage/World.h"
#include "System/Stage/StageData.h"
#include "System/Stage/StageInfo.h"

// Utilities
#include "System/Utility/ObjUtil.h"