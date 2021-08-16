#pragma once
#include <stdio.h>

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
#include "Sonicteam/System/MallocAllocator.h"


#ifdef LWAPI_NETWORKING
// Sonicteam Hio Library
#include "Sonicteam/hio/HioCore.h"
#include "Sonicteam/hio/HioPacket.h"
#include "Sonicteam/hio/HioServer.h"
#include "Sonicteam/hio/HioClient.h"
#include "Sonicteam/hio/HioCore.inl"
#endif

// Include this early
#include "Hedgehog/Base/System/hhAllocator.h"

// Dummy standard library
#include "std-dummy/std-dummy.h"

// gindows
#include "gindows/gindows.h"

// Hedgehog Library
#include"Hedgehog/Base/Types/hhBaseTypes.h"
#include "Hedgehog/Base/System/hhBaseObject.h"
#include "Hedgehog/Base/System/hhReferencedObject.h"

// Hedgehog Reflection Library
#include "Hedgehog/Reflection/hhInternalClassMember.h"
#include "Hedgehog/Reflection/hhRflCustomAttribute.h"
#include "Hedgehog/Reflection/hhRflClassMember.h"
#include "Hedgehog/Reflection/hhRflClassEnum.h"
#include "Hedgehog/Reflection/hhRflClass.h"
#include "Hedgehog/Reflection/hhRflTypeInfo.h"
#include "Hedgehog/Reflection/hhRflTypeInfoRegistry.h"
#include "Hedgehog/Reflection/hhRflClassNameRegistry.h"
#include "Hedgehog/Reflection/hhDataResource.h"
#include "Hedgehog/Reflection/hhDataValue.h"
#include "Hedgehog/Reflection/hhVariantDataUtil.h"
#include "Hedgehog/Reflection/hhRflSerializeUtil.h"

// Hedgehog Library
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
#include "Hedgehog/Base/System/hhFrame.h"
#include "Hedgehog/Base/System/hhArray.h"
#include "Hedgehog/Base/System/hhIOStream.h"
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

// Hedgehog Game Messages
#include "Hedgehog/Game/Messages/MsgKill.h"
#include "Hedgehog/Game/Messages/MsgDeactivate.h"
#include "Hedgehog/Game/Messages/MsgGetPosition.h"
#include "Hedgehog/Game/Messages/MsgGetRotation.h"

// Hedgehog Game Library
#include "Hedgehog/Game/LuaScript.h"
#include "Hedgehog/Game/GameSequence.h"
#include "Hedgehog/Game/Game.h"
#include "Hedgehog/Game/GameDocument.h"
#include "Hedgehog/Game/GameMode.h"
#include "Hedgehog/Game/GameObjectSystem.h"
#include "Hedgehog/Game/GOComponent.h"
#include "Hedgehog/Game/GameObject.h"
#include "Hedgehog/Game/GameObjectHandle.h"
#include "Hedgehog/Game/GameService.h"

// Hedgehog Game Components
#include "Hedgehog/Game/goc/goc_Transform.h"
#include "Hedgehog/Game/goc/goc_EnemyTarget.h"

// Hedgehog File System Library
#include "Hedgehog/FileSystem/Index.h"

// Hedgehog Resource Library
#include "Hedgehog/Resource/hhResCommon.h"
#include "Hedgehog/Pack/System/hhPackFileHeader.h"
#include "Hedgehog/Pack/System/hhPackFile.h"
#include "Hedgehog/Resource/hhResourceTypeInfo.h"
#include "Hedgehog/Resource/hhResourceReflections.h"

// Hedgehog Graphics Library
#include "Hedgehog/Graphics/hhCameraParam.h"
#include "Hedgehog/Graphics/Resource/hhFxSceneParmeters.h"
#include "Hedgehog/Graphics/Manager/hhRenderManager.h"

// Hedgehog Graphics Components
#include "Hedgehog/Graphics/goc/goc_Visual.h"
#include "Hedgehog/Graphics/goc/goc_VisualTransformed.h"
#include "Hedgehog/Graphics/goc/goc_VisualModel.h"
#include "Hedgehog/Graphics/goc/goc_VisualContainer.h"

// Hedgehog Animation Library
#include "Hedgehog/Animation/Base/hhAnimationObject.h"
#include "Hedgehog/Animation/Base/hhAnimationNode.h"
#include "Hedgehog/Animation/Base/hhAnimationClip.h"
#include "Hedgehog/Animation/Base/hhAnimationListener.h"
#include "Hedgehog/Animation/Resource/hhCharAnimScript.h"
#include "Hedgehog/Animation/Base/hhAnimationCallback.h"
#include "Hedgehog/Animation/Resource/hhAnimationResContainer.h"
#include "Hedgehog/Animation/hhAnimationManager.h"
#include "Hedgehog/Animation/hhSkeletonBlender.h"
#include "Hedgehog/Animation/hhSkeletonControl.h"
#include "Hedgehog/Animation/hhAnimSkeltonControl.h"
#include "Hedgehog/Animation/hhComplexBlender.h"
#include "Hedgehog/Animation/hhComplexImpl.h"
#include "Hedgehog/Animation/hhAnimationSimple.h"
#include "Hedgehog/Animation/hhAnimationComplex.h"
#include "Hedgehog/Animation/hhSimpleBlender.h"
#include "Hedgehog/Animation/hhExternalAnimation.h"
#include "Hedgehog/Animation/hhCallbackExecutioner.h"
#include "Hedgehog/Animation/hhAnimationNodeManager.h"
#include "Hedgehog/Animation/hhCharactorAnimation.h"
#include "Hedgehog/Animation/hhCharactorAnimationSingle.h"
#include "Hedgehog/Animation/hhCharactorAnimationMultiLayer.h"

// Hedgehog Animation Components
#include "Hedgehog/Animation/goc/goc_Animation.h"
#include "Hedgehog/Animation/goc/goc_AnimationSingle.h"
#include "Hedgehog/Animation/goc/goc_AnimationSimple.h"
#include "Hedgehog/Animation/goc/goc_AnimationScript.h"
#include "Hedgehog/Animation/goc/goc_AnimationScriptLayer.h"
#include "Hedgehog/Animation/goc/goc_AnimationContainer.h"

// Hedgehog Physics Components
#include "Hedgehog/Physics/goc/goc_Collider.h"
#include "Hedgehog/Physics/goc/goc_Physics.h"

// Hedgehog Sound Library
#include "Hedgehog/Sound/Resource/ResSoundCueInfoDataTag.h"
#include "Hedgehog/Sound/Debug/SoundInfo.h"
#include "Hedgehog/Sound/hhSoundDeviceTag.h"
#include "Hedgehog/Sound/hhSoundParam.h"
#include "Hedgehog/Sound/hhSoundHandleObj.h"
#include "Hedgehog/Sound/hhSoundHandle.h"
#include "Hedgehog/Sound/hhSoundListenerHandle.h"
#include "Hedgehog/Sound/hhSoundPlayer.h"
#include "Hedgehog/Sound/goc/goc_Sound.h"
#include "Hedgehog/Sound/hhSoundHandle.inl"
#include "Hedgehog/Sound/hhSoundListenerHandle.inl"

// System
#include "System/Singleton.h"
#include "System/ApplicationWin.h"
#include "System/DeviceWin.h"
#include "System/Messages.h"
#include "System/ObjInfo.h"
#include "System/FileLoader.h"
#include "System/ResourceManager.h"
#include "System/DeviceManager.h"

// System Game
#include "System/Game/ActorGroupRegistry.h"

// System Font
#include "System/Font/Font.h"
#include "System/Font/FontText.h"
#include "System/Font/FontManager.h"

// System Development
#include "System/Development/Variable.h"
#include "System/Development/VariableGroup.h"
#include "System/Development/VariableEditControl.h"
#include "System/Development/ReflectionEditControl.h"
#include "System/Development/FileStreamWin32.h"
#include "System/Development/HostFileSystem.h"
#include "System/Development/HostFileSystemWin32.h"

// System Debug
#include "System/Debug/Allocator.h"
#include "System/Debug/Object.h"
#include "System/Debug/Menu/MenuItem.h"
#include "System/Debug/Menu/Menu.h"
#include "System/Debug/Menu/MenuManager.h"
#include "System/Debug/FormObject.h"

#include "System/Development/ReflectionEditWindow.h"

#ifdef LWAPI_NETWORKING
#include "System/Debug/HioServer.h"
#endif

// Services
#include "System/Services/service_ObjInfoContainer.h"
#include "System/Services/service_LevelInfo.h"
#include "System/Services/service_SceneParameters.h"
#include "System/Services/service_FxColManager.h"
#include "System/Services/service_GameServiceTypeRegistry.h"

// Objects
#include "Hedgehog/Game/GameObject3D.h"

// SetData
#include "System/ObjectSystem/Resource/Object.h"
#include "System/ObjectSystem/Placement/WorldHandle.h"
#include "System/ObjectSystem/Placement/Actor.h"
#include "System/ObjectSystem/Placement/ActorPack.h"
#include "System/ObjectSystem/Placement/ActorManager.h"
#include "System/ObjectSystem/Activation/ActivationHandle.h"
#include "System/ObjectSystem/Activation/ActivationVolume.h"
#include "System/ObjectSystem/Activation/ActivationManager.h"
#include "System/ObjectSystem/MyActivationHandle.h"
#include "System/ObjectSystem/SetAdapter.h"
#include "System/ObjectSystem/Object.h"
#include "System/ObjectSystem/Manager/SetObjectManager.h"
#include "System/ObjectSystem/SetObjectListener.h"

// Stage Data
#include "System/Stage/World.h"
#include "System/Stage/StageData.h"
#include "System/Stage/StageInfo.h"

#include "System/Camera/Camera.h"
#include "System/Camera/CameraController.h"
#include "System/Camera/CameraUtil.h"
#include "System/Camera/MsgPushCameraController.h"
#include "System/Camera/MsgPopCameraController.h"
#include "System/Camera/MsgCameraUpdate.h"

#include "System/Player/GOCCollection.h"
#include "System/Player/Player.h"
#include "System/Player/GOCReferenceHolder.h"
#include "System/Player/VisualBase.h"
#include "System/Player/PlayerVisual.h"
#include "System/Player/VisualGOC.h"
#include "System/Player/StateGOC.h"
#include "System/Player/StateUtil.h"

// Utilities
#include "System/Utility/ObjUtil.h"