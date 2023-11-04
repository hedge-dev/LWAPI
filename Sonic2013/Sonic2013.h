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
#include "Sonicteam/System/poolheap.h"
#include "Sonicteam/System/stackheap.h"
#include "Sonicteam/System/freelistheap.h"
#include "Sonicteam/System/linkheap.h"
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
#include "Hedgehog/Base/System/BaseObject.h"
#include "Hedgehog/Base/System/ReferencedObject.h"
#include "Hedgehog/Base/Type/hhCowData.h"
#include "Hedgehog/Base/Type/hhSharedString.h"
#include "Hedgehog/Base/System/hhSymbol.h"
#include "Hedgehog/Base/hhBase.h"

// Hedgehog Reflection Library
#include "Hedgehog/Reflection/InternalClassMember.h"
#include "Hedgehog/Reflection/RflCustomAttribute.h"
#include "Hedgehog/Reflection/RflClassMember.h"
#include "Hedgehog/Reflection/RflClassEnum.h"
#include "Hedgehog/Reflection/RflClass.h"
#include "Hedgehog/Reflection/RflTypeInfo.h"
#include "Hedgehog/Reflection/RflTypeInfoRegistry.h"
#include "Hedgehog/Reflection/RflClassNameRegistry.h"
#include "Hedgehog/Reflection/DataResource.h"
#include "Hedgehog/Reflection/DataValue.h"
#include "Hedgehog/Reflection/VariantDataUtil.h"
#include "Hedgehog/Reflection/RflSerializeUtil.h"

// Hedgehog Library
#include "Hedgehog/Base/System/hhRefCountObject.h"
#include "Hedgehog/Base/System/RefByHandleObject.h"
#include "Hedgehog/Base/System/HandleManagerBase.h"
#include "Hedgehog/Base/System/Handle.h"
#include "Hedgehog/Base/System/Property.h"
#include "Hedgehog/Base/System/SyncTimer.h"
#include "Hedgehog/Base/System/PadData.h"
#include "Hedgehog/Base/System/DevicePlatformBase.h"
#include "Hedgehog/Base/System/DeviceBase.h"
#include "Hedgehog/Base/System/Application.h"
#include "Hedgehog/Base/System/HFrame.h"
#include "Hedgehog/Base/System/Array.h"
#include "Hedgehog/Base/System/InplaceArray.h"
#include "Hedgehog/Base/System/IOStream.h"
#include "System/GlobalAllocator.h"
#include "Hedgehog/Base/System/InplaceTempArray.h"

// Hedgehog Utility Library
#include "Hedgehog/Base/Utility/ScopedPointer.h"
#include "Hedgehog/Base/Utility/ScopedComPtr.h"
#include "Hedgehog/Base/Utility/ReferencePointer.h"
#include "Hedgehog/Base/Utility/TempArray.h"
#include "Hedgehog/Base/Utility/Utils.h"

// Hedgehog Memory Library
#include "Hedgehog/Base/Memory/PooledAllocator.h"

// Hedgehog Universe Library
#include "Hedgehog/Base/Universe/Message.h"
#include "Hedgehog/Base/Universe/MessageManager.h"
#include "Hedgehog/Base/Universe/Actor.h"
#include "Hedgehog/Base/Universe/LeafActor.h"
#include "Hedgehog/Base/Universe/BranchActor.h"

// Hedgehog Resource Library
#include "Hedgehog/Resource/hhResCommon.h"
#include "Hedgehog/Pack/System/hhPackFileHeader.h"
#include "Hedgehog/Pack/System/hhPackFile.h"
#include "Hedgehog/Resource/hhResourceTypeInfo.h"
#include "Hedgehog/Resource/hhResNameAc.h"
#include "Hedgehog/Resource/hhResourceReflections.h"
#include "Hedgehog/Resource/hhResTextureAc.h"
#include "Hedgehog/Resource/ResPathObject.h"

#include "Utility/ResCommon.h"

#include "Hedgehog/Database/Resource/hhSampleChunkResource.h"
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
#include "Hedgehog/FileSystem/Debug/dbg_FileInfo.h"
#include "Hedgehog/FileSystem/FileHandle.h"
#include "Hedgehog/FileSystem/FileCache.h"
#include "Hedgehog/FileSystem/FileSystem.h"
#include "Hedgehog/FileSystem/FileBinder.h"
#include "Hedgehog/FileSystem/FileReader.h"

#include "Hedgehog/Rsdx/Types.h"

// Hedgehog Graphics Library
#include "Hedgehog/MirageCore/RenderData/hhCVertexShaderData.h"
#include "Hedgehog/MirageCore/RenderData/hhCPixelShaderData.h"
#include "Hedgehog/MirageCore/RenderData/hhCVertexDeclarationPtr.h"
#include "Hedgehog/MirageCore/Misc/hhRenderingDevice.h"
#include "Hedgehog/MirageCore/Misc/hhRenderingInfrastructure.h"
#include "Hedgehog/Graphics/hhGraphics.h"

// Hedgehog Game Components
#include "Hedgehog/Game/goc/goc_Transform.h"
#include "Hedgehog/Game/goc/goc_EnemyTarget.h"

// Hedgehog Input Library
#include "Hedgehog/Input/goc/goc_CharacterInput.h"
#include "Hedgehog/MirageCore/Misc/hhRenderingDevice.inl"
#include "Hedgehog/MirageCore/RenderData/hhCVertexDeclarationPtr.inl"

// Hedgehog Animation Library
#include "Hedgehog/Animation/hhAnimObject.h"
#include "Hedgehog/Animation/Base/SkeletonBase.h"
#include "Hedgehog/Animation/Base/AnimationObj.h"
#include "Hedgehog/Animation/Base/AnimationNode.h"
#include "Hedgehog/Animation/Base/AnimationClip.h"
#include "Hedgehog/Animation/Base/AnimationListener.h"
#include "Hedgehog/Animation/Resource/ResCharAnimScript.h"
#include "Hedgehog/Animation/Base/AnimationCallback.h"
#include "Hedgehog/Animation/Resource/AnimationResContainer.h"
#include "Hedgehog/Animation/AnimationPlayingData.h"
#include "Hedgehog/Animation/AnimationTransition.h"
#include "Hedgehog/Animation/AnimationManager.h"
#include "Hedgehog/Animation/SkeletonBlender.h"
#include "Hedgehog/Animation/SkeletonControl.h"
#include "Hedgehog/Animation/AnimSkeletonControl.h"
#include "Hedgehog/Animation/ComplexImpl.h"
#include "Hedgehog/Animation/AnimationComplexBlender.h"
#include "Hedgehog/Animation/AnimationComplexSequence.h"
#include "Hedgehog/Animation/AnimationSimple.h"
#include "Hedgehog/Animation/AnimationComplex.h"
#include "Hedgehog/Animation/SimpleBlender.h"
#include "Hedgehog/Animation/ExternalAnimation.h"
#include "Hedgehog/Animation/CallbackExecutioner.h"
#include "Hedgehog/Animation/AnimationNodeManager.h"
#include "Hedgehog/Animation/CharactorAnimation.h"
#include "Hedgehog/Animation/CharactorAnimationSingle.h"
#include "Hedgehog/Animation/CharactorAnimationMultiLayer.h"
#include "Hedgehog/Animation/hhAnimMorphTargetNode.h"
#include "Hedgehog/Animation/hhAnimMorphTargetControl.h"

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
#include "Hedgehog/Sound/Debug/dbg_SoundInfo.h"
#include "Hedgehog/Sound/hhSoundDeviceTag.h"
#include "Hedgehog/Sound/hhSoundParam.h"
#include "Hedgehog/Sound/hhSoundHandleObj.h"
#include "Hedgehog/Sound/SoundHandle.h"
#include "Hedgehog/Sound/hhSoundListenerHandle.h"
#include "Hedgehog/Sound/SoundSystem.h"
#include "Hedgehog/Sound/SoundPlayer.h"
#include "Hedgehog/Sound/goc/goc_Sound.h"
#include "Hedgehog/Sound/SoundHandle.inl"
#include "Hedgehog/Sound/hhSoundListenerHandle.inl"

// Hedgehog Movie
#include "Hedgehog/Movie/MovieSystem.h"
#include "Hedgehog/Movie/MoviePlayer.h"

// Hedgehog Extras
#include "Hedgehog/Extra/Schedule/hhFxPipelineExecutor.h"

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

#include "game/goc/persistence/PersistenceObj.h"
#include "game/goc/hud/goc_HudCollider.h"
#include "game/goc/hud/goc_Hud.h"

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
#include "Hedgehog/Path/path_PathManager.h"
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
#include "SaveData/SaveDataAc.h"
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

#include "Hedgehog/Graphics/goc/Impl/goc_VisualModelImplHH.inl"
#include "Hedgehog/Game/GameSequence.inl"
#include "Hedgehog/Game/GameMode.inl"
#include "Hedgehog/Game/Game.inl"
#include "Hedgehog/Path/PathComponent.inl"
#include "Hedgehog/Movement/MoveBound.inl"

#include "lua/lua.h"

#ifdef _WIN32
	#ifdef _DEBUG
		#if defined(_MT) && defined(_DLL)
			#pragma comment(lib, __FILE__"/../lua/libs/lua-debug-mt.lib")
		#else
			#pragma comment(lib, __FILE__"/../lua/libs/lua-debug-md.lib")
		#endif
	#else
		#if defined(_MT) && defined(_DLL)
			#pragma comment(lib, __FILE__"/../lua/libs/lua-release-mt.lib")
		#else
			#pragma comment(lib, __FILE__"/../lua/libs/lua-release-md.lib")
		#endif
	#endif
	#pragma comment(lib, __FILE__"/../lua/libs/s13lua.lib")
#endif