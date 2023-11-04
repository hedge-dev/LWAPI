#pragma once

namespace app
{
	static bool IsGrindPathSearchRadiusSet = false;
	static float GringPathSearchRadius = 0.0f;

	static bool IsSVPathSearchRadiusSet = false;
	static float SVPathSearchRadius = 0.0f;

	namespace game
	{
		class PathManager;
		class PathRaycastInput;
		class PathRaycastOutput;
	}

	namespace ObjUtil
	{
		namespace detail
		{
			template <typename T>
			inline game::PathComponent* GetGravityPath(const game::GravityField* in_pGravityField)
			{
				T* pGravityField = csl::ut::DynamicCast<T, game::GravityField>(const_cast<game::GravityField*>(in_pGravityField));
				if (!pGravityField)
					return { nullptr };
			
				return pGravityField->GetPath();
			}
		}

		enum EFilter
		{
			eFilter_Default = 0,
			eFilter_Unk1,
			eFilter_Unk2,
			eFilter_Unk3,
			eFilter_Unk4,
			eFilter_Unk5,
			eFilter_Unk6,
			eFilter_Unk7,
			eFilter_Unk8,
			eFilter_Unk9,
			eFilter_Unk10,
			eFilter_Unk11,
			eFilter_Unk12,
			eFilter_Unk13,
			eFilter_Unk14,
			eFilter_Unk15,
			eFilter_Unk16,
			eFilter_Unk17,
		};

		template <size_t Len>
		class ResModelFixedContainer
		{
		public:
			csl::ut::FixedArray<hh::gfx::res::ResModel, Len> Models{};
		};

		template <size_t Len>
		class ResSkeletonFixedContainer
		{
		public:
			csl::ut::FixedArray<hh::gfx::res::ResSkeleton, Len> Skeletons{};
		};

		template <size_t Len>
		class ResCharAnimFixedContainer
		{
		public:
			csl::ut::FixedArray<hh::gfx::res::ResAnimSkeleton, Len> Animations{};
		};

		template <size_t Len>
		class ResTexSrtAnimFixedContainer
		{
		public:
			csl::ut::FixedArray<hh::gfx::res::ResAnimTexSrt, Len> Animations{};
		};

		static CObjInfo* GetObjectInfo(GameDocument& in_rDocument, const char* in_pName)
		{
			return in_rDocument.GetService<CObjInfoContainer>()->GetInfo(in_pName);
		}

		template <class T>
		static T* GetObjectInfo(GameDocument& in_rDocument)
		{
			return reinterpret_cast<T*>(GetObjectInfo(in_rDocument, T::ms_pName));
		}

		static const char* GetStagePackName(GameDocument& in_rDocument)
		{
			static csl::ut::FixedString<32> buffer{};

			auto* pLvlInfo = in_rDocument.GetService<CLevelInfo>();
			buffer.setf("%s_obj.pac", pLvlInfo->Level);

			return buffer;
		}

		static hh::ut::PackFile GetPackFile(const char* in_pName)
		{
			const auto data = csl::fnd::Singleton<fnd::ResourceManager>::GetInstance()->Get<fnd::ResRawData>(in_pName);
			if (!data.IsValid())
				return { nullptr };

			return (data->GetAddress());
		}

		static hh::gfx::res::ResTexture GetResTexture(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<hh::gfx::res::ResTexture>(in_pName);
		}

		static hh::gfx::res::ResModel GetModelResource(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<hh::gfx::res::ResModel>(in_pName);
		}

		template <size_t Len>
		static ResModelFixedContainer<Len> GetLodModelResource(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			static csl::ut::FixedString<128> buffer{};
			ResModelFixedContainer<Len> container{};

			if (!in_rPackFile.IsValid())
				return { container };

			container.Models[0] = GetModelResource(in_pName, in_rPackFile);
			for (size_t i = 1; i < Len; i++)
			{
				buffer.setf("%s_lod%02d", in_pName, i - 1);
				container.Models[i] = in_rPackFile.Get<hh::gfx::res::ResModel>(buffer);
			}
		}

		static res::ResShadowModel GetShadowModel(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<res::ResShadowModel>(in_pName);
		}

		static hh::gfx::res::ResSkeleton GetSkeletonResource(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<hh::gfx::res::ResSkeleton>(in_pName);
		}

		static hh::gfx::res::ResAnimSkeleton GetAnimationResource(const char* in_pName, hh::ut::PackFile& rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<hh::gfx::res::ResAnimSkeleton>(in_pName);
		}

		static app::ResCharAnimScript GetAnimationScriptResource(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<app::ResCharAnimScript>(in_pName);
		}

		static ResPhysicsMesh GetPhysicsMeshResource(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<ResPhysicsMesh>(in_pName);
		}

		static hh::gfx::res::ResAnimTexSrt GetTexSrtAnimationResource(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<hh::gfx::res::ResAnimTexSrt>(in_pName);
		}

		static hh::gfx::res::ResAnimVis GetVisAnimationResource(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<hh::gfx::res::ResAnimVis>(in_pName);
		}

		static hh::gfx::res::ResAnimMaterial GetMaterialAnimationResource(const char* in_pName, hh::ut::PackFile& in_rPackFile)
		{
			if (!in_rPackFile.IsValid())
				return { nullptr };

			return in_rPackFile.Get<hh::gfx::res::ResAnimMaterial>(in_pName);
		}

		static int GetPlayerActorID(GameDocument& in_rDocument, int in_playerNo)
		{
			auto* pLevelInfo = in_rDocument.GetService<CLevelInfo>();
			return pLevelInfo->GetPlayerID(in_playerNo);
		}

		static int GetPlayerNo(GameDocument& in_rDocument, uint in_actorID)
		{
			auto* pLevelInfo = in_rDocument.GetService<CLevelInfo>();
			return pLevelInfo->GetPlayerNo(in_actorID);
		}

		static xgame::PlayerInformation* GetPlayerInformation(GameDocument& in_rDocument, int in_playerNo)
		{
			auto* pLevelInfo = in_rDocument.GetService<CLevelInfo>();
			if (in_playerNo < 0 || pLevelInfo->GetNumPlayers() <= in_playerNo)
				return { nullptr };

			return in_rDocument.GetService<xgame::Blackboard>()->GetPlayerInformation(in_playerNo);
		}

		static void SetPropertyLockonTarget(GameObject* in_pObject)
		{
			in_pObject->SetProperty(0x4002, { 1 });
		}

		static void SetupCollisionFilter(EFilter in_filter, game::ColliShapeCInfo& in_rInfo)
		{
			switch (in_filter)
			{
			case eFilter_Unk1:
				in_rInfo.Unk7 = 18;
				in_rInfo.Unk8 = 0xB0000;
				break;
			case eFilter_Unk2:
				in_rInfo.Unk7 = 18;
				in_rInfo.Unk8 = 0x40000;
				break;
			case eFilter_Unk3:
			case eFilter_Unk4:
				in_rInfo.Unk7 = 18;
				in_rInfo.Unk8 = 0x80000;
				break;
			case eFilter_Unk5:
				in_rInfo.Unk7 = 18;
				in_rInfo.Unk8 = 0x5F0000;
				break;
			case eFilter_Unk6:
				in_rInfo.Unk7 = 25;
				in_rInfo.Unk8 = 0x30000;
				break;
			case eFilter_Unk7:
				in_rInfo.Unk7 = 25;
				in_rInfo.Unk8 = 0x800000;
				break;
			case eFilter_Unk8:
				in_rInfo.Unk7 = 22;
				in_rInfo.Unk8 = 0x30000;
				break;
			case eFilter_Unk9:
			case eFilter_Unk10:
				in_rInfo.Unk7 = 19;
				in_rInfo.Unk8 = 0x30000;
				break;
			case eFilter_Unk11:
				in_rInfo.Unk7 = 16;
				in_rInfo.Unk8 = 0x4C0000;
				break;
			case eFilter_Unk12:
				in_rInfo.Unk7 = 20;
				in_rInfo.Unk8 = 0x200000;
				break;
			case eFilter_Unk13:
				in_rInfo.Unk7 = 21;
				in_rInfo.Unk8 = 0;
				break;
			case eFilter_Unk14:
				in_rInfo.Unk7 = 16;
				in_rInfo.Unk8 = 0x5F0000;
				break;
			case eFilter_Unk15:
				in_rInfo.Unk7 = 16;
				in_rInfo.Unk8 = 0xE0000;
				break;
			case eFilter_Unk16:
				in_rInfo.Unk7 = 29;
				in_rInfo.Unk8 = 0x540000;
				break;
			case eFilter_Unk17:
				in_rInfo.Unk7 = 17;
				in_rInfo.Unk8 = 0x5F0000;
				break;
			default:
				in_rInfo.Unk7 = 18;
				in_rInfo.Unk8 = 0x30000;
				break;
			}
		}

		static void SetEnableColliShape(game::GOCCollider* in_pCollider, size_t in_shapeId, bool in_enable)
		{
			if (auto* pShape = in_pCollider->GetShapeById(in_shapeId))
				pShape->SetEnable(in_enable);
		}

		static void SetEnableColliShape(game::ColliShape* in_pShape, bool in_enable)
		{
			in_pShape->SetEnable(in_enable);
		}

		static bool SendMessageImmToPlayer(const GameObject& in_rObject, int playerNo, fnd::Message& in_rMessage)
		{
			auto* pDocument = in_rObject.GetDocument();
			uint actorID = ObjUtil::GetPlayerActorID(*pDocument, playerNo);
			return in_rObject.SendMessageImm(actorID, in_rMessage);
		}

		static bool SendMessageImmToPlayer(const GameObject& in_rObject, fnd::Message& in_rMessage)
		{
			return SendMessageImmToPlayer(in_rObject, 0, in_rMessage);
		}

		static void SendMessageImmToGameActor(const GameObject& in_rObject, fnd::Message& in_rMessage)
		{
			auto* pDocument = in_rObject.GetDocument();
			uint gameActorID = pDocument->GetGameActorID();
			in_rObject.SendMessageImm(gameActorID, in_rMessage);
		}

		static bool SendMessageImmToCamera(GameObject& in_rObject, int in_playerNo, fnd::Message& in_rMessage)
		{
			auto* pLevelInfo = in_rObject.GetDocument()->GetService<CLevelInfo>();
			if (!pLevelInfo)
				return false;

			return in_rObject.SendMessageImm(pLevelInfo->Cameras[in_playerNo], in_rMessage);
		}

		static bool SendMessageImmToCamera(GameObject& in_rObject, fnd::Message& in_rMessage)
		{
			return SendMessageImmToCamera(in_rObject, 0, in_rMessage);
		}

		static void SendMessageToSetObject(const GameObject& in_rObject, const CSetObjectID& in_rId, fnd::Message& in_rMessage, bool in_create)
		{
			auto* pDocument = in_rObject.GetDocument();
			auto* pSetMgr = pDocument->GetService<CSetObjectManager>();
			pSetMgr->SendObjectMessage(in_rId, in_rMessage, in_rObject.GetID(), in_create);
		}

		static bool SendMessageImmToSetObject(const GameObject& in_rObject, const CSetObjectID& in_rId, fnd::Message& in_rMessage, bool in_create)
		{
			auto* pDocument = in_rObject.GetDocument();
			auto* pSetMgr = pDocument->GetService<CSetObjectManager>();
			if (!pSetMgr)
				return false;

			return pSetMgr->SendObjectMessageImm(in_rId, in_rMessage, in_rObject.GetID(), in_create);
		}

		static GameObjectHandle<CSetObjectListener> GetGameObjectHandle(const GameDocument& in_rDocument, const CSetObjectID& in_rId, size_t in_unit)
		{
			auto* pSetMan = in_rDocument.GetService<CSetObjectManager>();
			if (!pSetMan)
				return nullptr;
			
			ut::RefPtr<CSetObject> setObj{};
			pSetMan->GetSetObjectFromUniqID(setObj, in_rId.Value);
			if (!setObj)
			{
				return nullptr;
			}

			return setObj->GetNthObject(in_unit);
		}

		static GameObjectHandle<CSetObjectListener> GetGameObjectHandle(const GameDocument& in_rDocument, const CSetObjectID& in_rId)
		{
			return GetGameObjectHandle(in_rDocument, in_rId, 0);
		}

		static bool GetSetObjectTransform(const GameDocument& in_rDocument, const CSetObjectID& in_rId, csl::math::Vector3* out_pPosition, csl::math::Quaternion* out_pRotation)
		{
			auto* pObjMan = in_rDocument.GetService<CSetObjectManager>();
			if (!pObjMan)
				return false;

			auto resObj = pObjMan->GetResObjectByID(in_rId);
			if (!resObj)
				return false;

			auto unit = resObj.GetUnit(0);
			if (!unit.IsValid())
				return false;
			
			if (out_pPosition)
				*out_pPosition = unit.GetPosition();
		
			if (out_pRotation)
				*out_pRotation = SetEd::CalcRotationByAngle(unit.GetRotation());

			return true;
		}

		static GameObjectHandle<CSetObjectListener> CreateSetObject(const GameDocument& in_rDocument, const CSetObjectID& in_rId)
		{
			auto* pObjMan = in_rDocument.GetService<CSetObjectManager>();
			if (!pObjMan)
				return nullptr;

			return pObjMan->CreateObjectBySetObjectID(in_rId);
		}

		static void AddScore(GameObject& in_rGameObject, const char* in_pName, xgame::MsgDamageBase& in_rMessage, csl::math::Vector3& in_rPosition)
		{
			if (in_rMessage.PlayerNo < 0)
				return;
		
			xgame::MsgScore msgScore{};
			msgScore.pName = in_pName;
			msgScore.Position = in_rPosition;
			msgScore.PlayerNo = in_rMessage.PlayerNo;
			msgScore.BonusData = in_rMessage.Bonus;

			in_rGameObject.SendMessageImm(in_rGameObject.GetDocument()->GetGameActorID(), msgScore);
		}

		static void AddScore(GameObject& in_rGameObject, const char* in_pName, int in_playerNo, const csl::math::Vector3& in_rPosition)
		{
			if (in_playerNo < 0)
				return;

			xgame::MsgScore msg{};
			msg.pName = in_pName;
			msg.Position = in_rPosition;
			msg.PlayerNo = in_playerNo;

			in_rGameObject.SendMessageImm(in_rGameObject.GetDocument()->GetGameActorID(), msg);
		}

		static void AddScore(GameObject& in_rGameObject, const char* in_pName, xgame::MsgDamageBase& in_rMessage)
		{
			auto position = in_rGameObject.GetComponent<fnd::GOCTransform>()->Frame.Unk3.GetTranslation();
			AddScore(in_rGameObject, in_pName, in_rMessage, position);
		}

		static void AddScorePlayerAction(GameObject& in_rGameObject, const char* in_pName, int in_playerNo)
		{
			if (in_playerNo < 0)
				return;

			auto* pTransform = in_rGameObject.GetComponent<fnd::GOCTransform>();
			if (!pTransform)
				return;
		
			xgame::MsgScore msg{};
			msg.pName = in_pName;
			msg.Position = pTransform->Frame.Unk3.GetTranslation();
			msg.PlayerNo = in_playerNo;
			in_rGameObject.SendMessageImm(in_rGameObject.GetDocument()->GetGameActorID(), msg);
		}

		static game::PathManager* GetPathManager(GameDocument& in_rDocument)
		{
			return in_rDocument.GetService<game::PathManager>();
		}

		static bool RaycastNearestCollision(game::PhysicsRaycastOutput* out_pOutput, GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, uint in_filter)
		{
			if (auto* pPhysicsWorld = in_rDocument.GetService<CPhysicsWorld>())
				return pPhysicsWorld->Raycast(in_rFrom, in_rTo, in_filter, out_pOutput);
			
			return false;
		}

		static bool RaycastHitCollision(GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, uint in_filter)
		{
			game::PhysicsRaycastOutput output{};
			return RaycastNearestCollision(&output, in_rDocument, in_rFrom, in_rTo, in_filter);
		}
		
		static bool GetSearchPathObjByRaycast(GameDocument& in_rDocument, const game::PathRaycastInput& in_rInput, game::PathRaycastOutput* out_pOutput)
		{
			auto* pathManager = GetPathManager(in_rDocument);
			return pathManager && pathManager->CastRay(in_rInput, out_pOutput);
		}

		static bool RaycastGrindPath(GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, game::PathRaycastOutput* out_pOutput)
		{
			game::PathRaycastInput input{ in_rFrom, in_rTo, 1, 8 };
			if (GetSearchPathObjByRaycast(in_rDocument, input, out_pOutput))
				return out_pOutput->pComponent != nullptr;

			return false;
		}

		static bool SearchNearestGrindPath(GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, game::PathRaycastOutput* out_pOutput)
		{
			if (!IsGrindPathSearchRadiusSet)
			{
				IsGrindPathSearchRadiusSet = true;
				GringPathSearchRadius = 400.0f;
			}

			csl::math::Vector3 to{ in_rFrom + (in_rTo * GringPathSearchRadius) };
			return RaycastGrindPath(in_rDocument, in_rFrom, to, out_pOutput);
		}

		static game::PathComponent* GetSVPath(GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo)
		{
			if (!IsSVPathSearchRadiusSet)
			{
				IsSVPathSearchRadiusSet = true;
				SVPathSearchRadius = 400.0f;
			}

			csl::math::Vector3 to{ in_rFrom + (in_rTo * SVPathSearchRadius) };
			game::PathRaycastInput input{ in_rFrom, to, 1, 1 };
			game::PathRaycastOutput output{};
			if (GetSearchPathObjByRaycast(in_rDocument, input, &output))
			{
				return output.pComponent;
			}

			return { nullptr };
		}

		static fnd::SoundHandle PlaySE(const char* in_pSoundName, const csl::math::Vector3& in_rPosition, fnd::SoundDeviceTag in_device)
		{
			auto* pSoundManager = csl::fnd::Singleton<fnd::SoundPlayer>::GetInstance();
			if (!pSoundManager)
				return { nullptr };

			fnd::SoundParam param{};
			param.TweenFactor = 0.0f;
			param.Device = in_device;

			return pSoundManager->Play3D(2, in_pSoundName, in_rPosition, param);
		}

		static fnd::SoundHandle PlaySE2D(const char* in_pSoundName, fnd::SoundDeviceTag in_device)
		{
			auto* pSoundManager = csl::fnd::Singleton<fnd::SoundPlayer>::GetInstance();
			if (!pSoundManager)
				return { nullptr };

			fnd::SoundParam param{};
			param.TweenFactor = 0.0f;
			param.Device = in_device;

			return pSoundManager->Play(2, in_pSoundName, param);
		}

		static bool CheckShapeUserID(const game::ColliShape* in_pShape, uint in_id)
		{
			if (!in_pShape)
				return false;

			return in_pShape->ID == in_id;
		}

		static bool CheckShapeUserID(const fnd::Handle<game::ColliShape>& in_rShapeHandle, uint in_id)
		{
			return CheckShapeUserID(in_rShapeHandle.Get(), in_id);
		}

		inline game::GravityField* GetGravityField(GameDocument& in_rDocument, const csl::math::Vector3& in_rPosition)
		{
			auto* pGravityManager = in_rDocument.GetService<game::GravityManager>();
			if (!pGravityManager)
				return { nullptr };

			return pGravityManager->GetObjectAtPoint(in_rPosition);
		}

		inline game::PathComponent* GetGravityPathCylinder(const game::GravityField* in_pGravityField)
		{
			return detail::GetGravityPath<game::GFieldCylinderSpline>(in_pGravityField);
		}

		inline game::PathComponent* GetGravityPathInsideCylinder(const game::GravityField* in_pGravityField)
		{
			return detail::GetGravityPath<game::GFieldInsideCylinderSpline>(in_pGravityField);
		}

		inline game::PathComponent* GetGravityPathSideview(const game::GravityField* in_pGravityField)
		{
			return detail::GetGravityPath<game::GFieldSvSpline>(in_pGravityField);
		}

		class LayoutCylinder
		{
		public:
			struct Description
			{
				fnd::HFrame* pFrame{};
				game::GravityField* pGravityField{};
				csl::ut::Bitset<uint> Flags{};
			};
	 
		private:
			inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x0073E410), LayoutCylinder*, const Description&);
			inline static FUNCTION_PTR(math::Transform*, __thiscall, ms_fpCalcTransform, ASLR(0x0073E520), LayoutCylinder*, math::Transform*, const csl::math::Vector3&);

		public:
			csl::math::Vector3 Unk1{};
			csl::math::Vector3 Unk2{};
			csl::math::Vector3 Unk3{};
			float Unk4{};
			game::PathEvaluator Path{};
			fnd::HFrame* pFrame{};
			csl::ut::Bitset<uint> Flags{};

		public:
			bool Setup(const Description& in_rDescription)
			{
				return ms_fpSetup(this, in_rDescription);
			}

			math::Transform* CalcTransform(const csl::math::Vector3& in_rVector)
			{
				math::Transform transform{};
				ms_fpCalcTransform(this, &transform, in_rVector);
			
				return &transform;
			}
		};
	}
}