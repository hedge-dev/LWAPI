#pragma once
#include <stdio.h>
#include "boost/smart_ptr/shared_ptr.hpp"

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
#include "Sonicteam/System/DummyLock.h"
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
#include "Sonicteam/Utility/collections/List.h"
#include "Sonicteam/Utility/collections/HashMap.h"
#include "Sonicteam/Utility/collections/PointerMap.h"
#include "Sonicteam/Utility/collections/StringMap.h"
#include "Sonicteam/Utility/collections/CircularBuffer.h"
#include "Sonicteam/Utility/VariableString.h"
#include "Sonicteam/Utility/FixedString.h"
#include "Sonicteam/Utility/Point.h"
#include "Sonicteam/Utility/Size.h"
#include "Sonicteam/Utility/Rectangle.h"
#include "Sonicteam/Utility/Color.h"
#include "Sonicteam/System/ComPtr.h"
#include "Sonicteam/System/MemorySnapshot.h"
#include "Sonicteam/System/HeapBase.h"
#include "Sonicteam/System/PoolHeapBase.h"
#include "Sonicteam/System/StackHeapBase.h"
#include "Sonicteam/System/FreeListHeapBase.h"
#include "Sonicteam/System/LinkHeapBase.h"
#include "Sonicteam/System/PoolHeapTemplate.h"
#include "Sonicteam/System/LinkHeapTemplate.h"
#include "Sonicteam/System/StackHeapTemplate.h"
#include "Sonicteam/System/FreeListHeapTemplate.h"
#include "Sonicteam/System/MallocAllocator.h"

#include "SonicUSA/System/Random.h"
#include "SonicUSA/System/RadianMask.h"

#ifdef LWAPI_NETWORKING
// Sonicteam Hio Library
#include "Sonicteam/hio/HioCore.h"
#include "Sonicteam/hio/HioPacket.h"
#include "Sonicteam/hio/HioServer.h"
#include "Sonicteam/hio/HioClient.h"
#include "Sonicteam/hio/HioCore.inl"
#endif

// Include this early
#include "Hedgehog/Base/Memory/hhAllocator.h"

// Dummy standard library
#include "std-dummy/std-dummy.h"

// gindows
#include "gindows/gindows.h"

// SurfRide Library
#include "SurfRide/Math.h"
#include "SurfRide/Color.h"
#include "SurfRide/Allocator.h"
#include "SurfRide/Base.h"
#include "SurfRide/ReferenceCount.h"
#include "SurfRide/BinaryData.h"
#include "SurfRide/SrCamera.h"
#include "SurfRide/Camera.h"
#include "SurfRide/Project.h"
#include "SurfRide/Scene.h"
#include "SurfRide/Animation.h"
#include "SurfRide/Layer.h"
#include "SurfRide/CastNode.h"
#include "SurfRide/ReferenceCast.h"

#include "SurfRide/Project.inl"
#include "SurfRide/Scene.inl"

// Hedgehog Library
#include "Hedgehog/Base/Type/hhBaseTypes.h"
#include "Hedgehog/Base/System/hhObject.h"
#include "Hedgehog/Base/System/hhBaseObject.h"
#include "Hedgehog/Base/System/hhReferencedObject.h"
#include "Hedgehog/Base/Type/hhCowData.h"
#include "Hedgehog/Base/Type/hhSharedString.h"
#include "Hedgehog/Base/System/hhSymbol.h"
#include "Hedgehog/Base/hhBase.h"

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
#include "Hedgehog/Base/System/hhInplaceArray.h"
#include "Hedgehog/Base/System/hhIOStream.h"
#include "System/GlobalAllocator.h"
#include "Hedgehog/Base/System/hhInplaceTempArray.h"

// Hedgehog Utility Library
#include "Hedgehog/Base/Utility/hhScopedPointer.h"
#include "Hedgehog/Base/Utility/hhReferencePointer.h"
#include "Hedgehog/Base/Utility/hhTempArray.h"
#include "Hedgehog/Base/Utility/hhUtils.h"

// Hedgehog Memory Library
#include "Hedgehog/Base/Memory/Pooled/hhPooledAllocatorBase.h"
#include "Hedgehog/Base/Memory/Pooled/hhPooledAllocator.h"
#include "Hedgehog/Base/Memory/Pooled/hhThreadSafePooledAllocator.h"

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
#include "Hedgehog/Resource/hhResName.h"
#include "Hedgehog/Resource/hhResourceReflections.h"
#include "Hedgehog/Resource/hhResTexture.h"
#include "Hedgehog/Resource/hhResPathObject.h"

#include "Utility/ResCommon.h"

#include "Hedgehog/Database/System/hhDatabaseData.h"

// Hedgehog Game Messages
#include "Hedgehog/Game/Messages/MsgKill.h"
#include "Hedgehog/Game/Messages/MsgDeactivate.h"
#include "Hedgehog/Game/Messages/MsgGetPosition.h"
#include "Hedgehog/Game/Messages/MsgGetRotation.h"
#include "Hedgehog/Game/Messages/MsgGetVelocity.h"

// Hedgehog Game Library
#include "Hedgehog/Game/Resource/ResNameExtra.h"
#include "Hedgehog/Game/TinyFsm.h"
#include "Hedgehog/Game/LuaScript.h"
#include "Hedgehog/Game/GameSequence.h"
#include "Hedgehog/Game/Game.h"
#include "Hedgehog/Game/GameDocument.h"
#include "Hedgehog/Game/GameMode.h"
#include "Hedgehog/Game/GameModeUtil.h"
#include "Hedgehog/Game/GameObjectSystem.h"
#include "Hedgehog/Game/GOComponent.h"
#include "Hedgehog/Game/GameObject.h"
#include "Hedgehog/Game/GameObjectHandle.h"
#include "Hedgehog/Game/GameService.h"
#include "Hedgehog/Game/HudLayerController.h"

#include "System/DisplaySwitch/DisplayText.h"
#include "System/DisplaySwitch/DisplaySwitch.h"

// Hedgehog File System Library
#include "Hedgehog/FileSystem/FileSystem.h"

#include "Hedgehog/Rsdx/Types.h"

// Hedgehog Graphics Library
#include "Hedgehog/MirageCore/RenderData/hhVertexShaderData.h"
#include "Hedgehog/MirageCore/RenderData/hhPixelShaderData.h"
#include "Hedgehog/MirageCore/RenderData/hhVertexDeclarationPtr.h"
#include "Hedgehog/MirageCore/Misc/hhRenderingDevice.h"
#include "Hedgehog/MirageCore/Misc/hhRenderingInfrastructure.h"
#include "Hedgehog/Graphics/hhGraphics.h"

// Hedgehog Game Components
#include "Hedgehog/Game/goc/goc_Transform.h"
#include "Hedgehog/Game/goc/goc_EnemyTarget.h"
#include "Hedgehog/Game/goc/hud/goc_HudCollider.h"
#include "Hedgehog/Game/goc/hud/goc_Hud.h"

// Hedgehog Input Library
#include "Hedgehog/Input/goc/goc_CharacterInput.h"

#include "Hedgehog/MirageCore/Misc/hhRenderingDevice.inl"
#include "Hedgehog/MirageCore/RenderData/hhVertexDeclarationPtr.inl"

// Hedgehog Animation Library
#include "Hedgehog/Animation/Base/hhAnimationObject.h"
#include "Hedgehog/Animation/Base/hhAnimationNode.h"
#include "Hedgehog/Animation/Base/hhAnimationClip.h"
#include "Hedgehog/Animation/Base/hhAnimationListener.h"
#include "Hedgehog/Animation/Resource/hhCharAnimScript.h"
#include "Hedgehog/Animation/Base/hhAnimationCallback.h"
#include "Hedgehog/Animation/Resource/hhAnimationResContainer.h"
#include "Hedgehog/Animation/hhPlayingData.h"
#include "Hedgehog/Animation/hhAnimationTransition.h"
#include "Hedgehog/Animation/hhAnimationManager.h"
#include "Hedgehog/Animation/hhSkeletonBlender.h"
#include "Hedgehog/Animation/hhSkeletonControl.h"
#include "Hedgehog/Animation/hhAnimSkeltonControl.h"
#include "Hedgehog/Animation/hhComplexImpl.h"
#include "Hedgehog/Animation/hhComplexBlender.h"
#include "Hedgehog/Animation/hhComplexSequence.h"
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

// Hedgehog Physics Library
#include "Hedgehog/Physics/hhPhysics.h"

#include "Hedgehog/Physics/goc/goc_Launcher.h"

// Hedgehog Effect Components
#include "Hedgehog/Effect/hhInstanceHandle.h"
#include "Hedgehog/Effect/goc/goc_Effect.h"

// Hedgehog Sound Library
#include "Hedgehog/Sound/Resource/ResSoundCueInfoDataTag.h"
#include "Hedgehog/Sound/Debug/SoundInfo.h"
#include "Hedgehog/Sound/hhSoundDeviceTag.h"
#include "Hedgehog/Sound/hhSoundParam.h"
#include "Hedgehog/Sound/hhSoundHandleObj.h"
#include "Hedgehog/Sound/hhSoundHandle.h"
#include "Hedgehog/Sound/hhSoundListenerHandle.h"
#include "Hedgehog/Sound/hhSoundSystem.h"
#include "Hedgehog/Sound/hhSoundPlayer.h"
#include "Hedgehog/Sound/goc/goc_Sound.h"
#include "Hedgehog/Sound/hhSoundHandle.inl"
#include "Hedgehog/Sound/hhSoundListenerHandle.inl"

// Hedgehog Movie
#include "Hedgehog/Movie/hhMovieSystem.h"
#include "Hedgehog/Movie/hhMoviePlayer.h"

// System
#include "System/Singleton.h"
#include "System/ApplicationWin.h"
#include "System/DeviceWin.h"
#include "System/Messages.h"
#include "System/ObjInfo.h"
#include "System/FileLoader.h"
#include "System/ResourceManager.h"
#include "System/DeviceManager.h"
#include "System/AocManager.h"
#include "System/TerrainBase.h"
#include "System/TerrainManager.h"
#include "System/FadeInOutManager.h"

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
#include "System/Debug/DrawContext.h"
#include "System/Debug/GraphicsGeometry.h"
#include "System/Debug/DrawSystem.h"

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
#include "System/Services/service_RingManager.h"
#include "System/Services/service_FootPrintManager.h"
#include "System/Services/service_SnowBallTrackManager.h"

// Objects
#include "Hedgehog/Game/GameObject3D.h"

// SetData
#include "System/ObjectSystem/Resource/Object.h"
#include "System/ObjectSystem/Resource/ClassProject.h"
#include "System/ObjectSystem/Resource/ObjectProject.h"
#include "System/ObjectSystem/detail/SetObjClass.h"
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
#include "System/ObjectSystem/ClassProject.h"
#include "System/ObjectSystem/ObjectProject.h"
#include "System/ObjectSystem/SetObjectFactory.h"
#include "System/ObjectSystem/Resource.h"
#include "System/ObjectSystem/Manager/SetObjectManager.h"
#include "System/ObjectSystem/SetObjectListener.h"

#include "System/ObjectSystem/Activation/ActivationHandle.inl"
#include "System/ObjectSystem/MyActivationHandle.inl"

// Stage Data
#include "Stage/World.h"
#include "Stage/StageData.h"
#include "Stage/StageInfo.h"
#include "Stage/StageDataInitializer.h"

#include "System/Player/BlackBoard.h"

// Utilities
#include "System/Utility/AabbTree.h"

#include "Hedgehog/Path/PathDebugDraw.h"
#include "Hedgehog/Path/PathCollisionHandler.h"
#include "Hedgehog/Path/PathCollisionHandlerStandard.h"
#include "Hedgehog/Path/PathComponent.h"
#include "Hedgehog/Path/PathManager.h"
#include "Hedgehog/Path/PathEvaluator.h"

#include "Stage/Shadow/Resource/ShadowModel.h"

#include "Hedgehog/Gravity/GravityEffect.h"
#include "Hedgehog/Gravity/SimpleGravityEffect.h"
#include "Hedgehog/Gravity/SplineGravityEffect.h"
#include "Hedgehog/Gravity/SvSplineGravityEffect.h"
#include "Hedgehog/Gravity/GravityField.h"
#include "Hedgehog/Gravity/GFieldCylinderSpline.h"
#include "Hedgehog/Gravity/GFieldSphere.h"
#include "Hedgehog/Gravity/GFieldHemisphere.h"
#include "Hedgehog/Gravity/GFieldOutsideCylinderSpline.h"
#include "Hedgehog/Gravity/GFieldInsideCylinderSpline.h"
#include "Hedgehog/Gravity/GFieldOutsidePrismSpline.h"
#include "Hedgehog/Gravity/GFieldInsidePrismSpline.h"
#include "Hedgehog/Gravity/GFieldSvSpline.h"
#include "Hedgehog/Gravity/goc/goc_Gravity.h"
#include "Hedgehog/Gravity/GravityManager.h"
#include "Hedgehog/Gravity/GravityController.h"

#include "System/Utility/ObjUtil.h"

#include "Stage/Debris/Resource/ResFixPositionDebris.h"
#include "Stage/Debris/Resource/ResRandomSpaceDebris.h"
#include "Stage/Debris/DebrisBaseInfo.h"
#include "Stage/Debris/RandomSpaceDebrisInfo.h"
#include "Stage/Debris/DebrisUtil.h"

// Hedgehog Shadow Components
#include "Hedgehog/Shadow/ShadowShape.h"
#include "Hedgehog/Shadow/ShadowSphereShape.h"
#include "Hedgehog/Shadow/ShadowHemisphereShape.h"
#include "Hedgehog/Shadow/ShadowModelShape.h"
#include "Hedgehog/Shadow/goc/goc_Shadow.h"
#include "Hedgehog/Shadow/goc/goc_ShadowSimple.h"

#include "System/Utility/StateBase.h"
#include "System/Utility/HsmImpl.h"
#include "System/Enemy/goc/goc_EnemyHsm.h"
#include "System/Enemy/EnemyState.h"
#include "System/Enemy/EnemyBlowOffObjectCInfo.h"
#include "System/Enemy/EnemyDeadEffect.h"
#include "System/Enemy/AnimalManager.h"
#include "System/Enemy/EnemyManager.h"
#include "System/Enemy/EnemySweepMove.h"

#include "Hedgehog/Movement/MovementUtility.h"
#include "Hedgehog/Movement/BarrierChecker.h"
#include "Hedgehog/Movement/MoveController.h"
#include "Hedgehog/Movement/goc/goc_Movement.h"
#include "Hedgehog/Movement/MoveBound.h"
#include "Hedgehog/Movement/MovePopup.h"
#include "Hedgehog/Movement/MoveStraight.h"
#include "Hedgehog/Movement/MoveCharacterRigidBody.h"
#include "Hedgehog/Movement/MoveObjGolonRock.h"
#include "Hedgehog/Movement/MoveEnemyKeese.h"
#include "Hedgehog/Movement/MoveObjCocco.h"
#include "Hedgehog/Movement/MoveVelocityReference.h"
#include "Hedgehog/Movement/goc/goc_MovementComplex.h"

#include "Hedgehog/Movement/goc/goc_Motor.h"
#include "Hedgehog/Movement/goc/goc_MotorRotate.h"

#include "System/Camera/Camera.h"
#include "System/Camera/CameraController.h"
#include "System/Camera/CameraUtil.h"
#include "System/Camera/MsgPushCameraController.h"
#include "System/Camera/MsgPopCameraController.h"
#include "System/Camera/MsgCameraUpdate.h"
#include "System/Camera/MsgCameraOn.h"
#include "System/Camera/MsgCameraOff.h"
#include "System/Camera/MsgCameraReset.h"
#include "System/Camera/MsgShakeCamera.h"

#include "System/Player/Info/PlayerVisualSonicInfo.h"
#include "System/Player/Info/PlayerVisualSuperSonicInfo.h"
#include "System/Player/Info/PlayerVisualVirtualSonicInfo.h"
#include "System/Player/Info/PlayerVehicleTornadoInfo.h"
#include "System/Player/Info/PlayerVehicleSnowBallInfo.h"
#include "System/Player/Info/PlayerVisualSonicZeldaInfo.h"
#include "System/Player/Info/PlayerVisualPhantomSpinInfo.h"
#include "System/Player/Info/PlayerVisualPhantomLaserInfo.h"
#include "System/Player/Info/PlayerVisualPhantomRocketInfo.h"
#include "System/Player/Info/PlayerVisualPhantomAsteroidInfo.h"
#include "System/Player/Info/PlayerVisualPhantomEagleInfo.h"
#include "System/Player/Info/PlayerVisualPhantomRhythmInfo.h"
#include "System/Player/Info/PlayerVisualPhantomHoverInfo.h"
#include "System/Player/Info/PlayerVisualPhantomBombInfo.h"
#include "System/Player/Info/PlayerVisualPhantomQuakeInfo.h"

#include "System/Player/ParameterSpeed.h"
#include "System/Player/PlayerUtil.h"
#include "System/Player/GOCCollection.h"
#include "System/Player/ParameterGOC.h"
#include "System/Player/Physics.h"
#include "System/Player/PathService.h"
#include "System/Player/HomingTargetService.h"
#include "System/Player/PlayerVehicle.h"
#include "System/Player/SnowBall.h"
#include "System/Player/PlaneTornado.h"
#include "System/Player/States.h"
#include "System/Player/GOCReferenceHolder.h"
#include "System/Player/CollisionGOC.h"
#include "System/Player/VisualGOC.h"
#include "System/Player/Player.h"
#include "System/Player/PlayerResourceInfoRegister.h"
#include "System/Player/VisualUtil.h"
#include "System/Player/VisualBase.h"
#include "System/Player/PlayerVisual.h"
#include "System/Player/VisualUnit.h"
#include "System/Player/VisualHuman.h"
#include "System/Player/VisualSonic.h"
#include "System/Player/State.h"
#include "System/Player/PluginBase.h"
#include "System/Player/StatePlugin.h"
#include "System/Player/StateGOC.h"
#include "System/Player/PlayerStateUtilEffect.h"
#include "System/Player/StateUtil.h"
#include "System/Player/Plugins.h"
#include "System/Player/Sonic.h"

#include "System/Player/StateGOC.inl"
#include "System/Player/Physics.inl"
#include "System/Player/Player.inl"
#include "System/Player/PathService.inl"
#include "System/Player/VisualGOC.inl"
#include "System/Player/PlayerVehicle.inl"
#include "System/Player/SnowBall.inl"
#include "System/Player/PlayerUtil.inl"

#include "System/Player/PlayerStateBase.h"

#include "System/Enemy/MoveEnemyBlowOffObject.h"
#include "System/Enemy/EnemyBlowOffObject.h"
#include "System/Enemy/EnemyUtil.h"
#include "System/Enemy/EnemyBase.h"
#include "System/Enemy/EnemyInfo.h"
#include "System/Enemy/EnemyUvAnimLinkController.h"
#include "Object/Objects.h"

#include "System/Player/PlayerStateUtilEffect.inl"
#include "System/Player/StateUtil.inl"

#include "SaveData/FlagSet.h"
#include "SaveData/FlagSet.inl"
#include "SaveData/GameData.h"
#include "SaveData/SaveData.h"
#include "SaveData/SaveManager.h"

// Hedgehog HUD Components
#include "HUD/HudGameMainDisplay.h"

#include "System/StandardGameUpdate.h"
#include "System/GameMode/GameModeStartUp.h"

#include "xgame/system/GameScore/GameScoreManager.h"
#include "xgame/system/DlcManager.h"
#include "xgame/system/DlcManager.inl"

#include "xgame/gamemode/stage/StagePhysicsSetup.h"
#include "xgame/gamemode/stage/StageSoundGuidePathControl.h"
#include "xgame/gamemode/stage/GlobalAmbCoordinator.h"
#include "xgame/gamemode/stage/BGMCoordinator.h"
#include "xgame/gamemode/stage/BGMParamCoordinator.h"
#include "xgame/gamemode/stage/StageSoundDirector.h"
#include "xgame/gamemode/stage/StageGameStatus.h"
#include "xgame/gamemode/stage/StatusCheckPoint.h"
#include "xgame/gamemode/e3title/GameModeE3Title.h"
#include "xgame/gamemode/openingmovie/GameModeOpeningMovie.h"
#include "xgame/gamemode/eventmovie/GameModeEventMovie.h"
#include "xgame/gamemode/gameover/GameOverInfo.h"
#include "xgame/gamemode/minigame/GameModeMinigame.h"
#include "xgame/gamemode/minigame/MinigameCharacterInfo.h"
#include "xgame/gamemode/WorldAreaMap/WorldMapDiorama.h"
#include "xgame/gamemode/WorldAreaMap/GameModeWorldAreaMap.h"
#include "xgame/gamemode/WorldAreaMap/WorldAreaMapObjResource.h"
#include "xgame/gamemode/WorldAreaMap/WorldAreaMapInfo.h"
#include "xgame/gamemode/WorldAreaMap/worldmap_diorama.h"
#include "xgame/gamemode/WorldAreaMap/worldmap_diorama_stage.h"

#include "System/GameMode/GameModeStage.h"
#include "xgame/gamemode/StageBattle/GameModeStageBattle.h"

#include "Hedgehog/Graphics/goc/Impl/goc_VisualModelImpl.inl"
#include "Hedgehog/Game/GameSequence.inl"
#include "Hedgehog/Game/GameMode.inl"
#include "Hedgehog/Game/Game.inl"
#include "Hedgehog/Path/PathComponent.inl"
#include "Hedgehog/Movement/MoveBound.inl"