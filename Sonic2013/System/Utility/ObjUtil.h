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

		static const char* GetStagePackName(GameDocument& rDocument)
		{
			static csl::ut::FixedString<32> buffer{};

			auto* pLvlInfo = rDocument.GetService<CLevelInfo>();
			buffer.setf("%s_obj.pac", pLvlInfo->m_Level);

			return buffer;
		}

		static hh::ut::PackFile GetPackFile(const char* pName)
		{
			const auto data = csl::fnd::Singleton<fnd::ResourceManager>::GetInstance()->Get<fnd::ResRawData>(pName);
			if (!data.IsValid())
				return { nullptr };

			return (data->GetAddress());
		}

		static hh::gfx::res::ResTexture GetResTexture(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResTexture>(pName);
		}

		static hh::gfx::res::ResModel GetModelResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResModel>(pName);
		}

		template <size_t Len>
		static ResModelFixedContainer<Len> GetLodModelResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			static csl::ut::FixedString<128> buffer{};
			ResModelFixedContainer<Len> container{};

			if (!rPackFile.IsValid())
				return { container };

			container.Models[0] = GetModelResource(pName, rPackFile);
			for (size_t i = 1; i < Len; i++)
			{
				buffer.setf("%s_lod%02d", pName, i - 1);
				container.Models[i] = rPackFile.Get<hh::gfx::res::ResModel>(buffer);
			}
		}

		static res::ResShadowModel GetShadowModel(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<res::ResShadowModel>(pName);
		}

		static hh::gfx::res::ResSkeleton GetSkeletonResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResSkeleton>(pName);
		}

		static hh::gfx::res::ResAnimSkeleton GetAnimationResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResAnimSkeleton>(pName);
		}

		static app::ResCharAnimScript GetAnimationScriptResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<app::ResCharAnimScript>(pName);
		}

		static ResPhysicsMesh GetPhysicsMeshResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<ResPhysicsMesh>(pName);
		}

		static hh::gfx::res::ResAnimTexSrt GetTexSrtAnimationResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResAnimTexSrt>(pName);
		}

		static hh::gfx::res::ResAnimVis GetVisAnimationResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResAnimVis>(pName);
		}

		static hh::gfx::res::ResAnimMaterial GetMaterialAnimationResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResAnimMaterial>(pName);
		}

		static int GetPlayerActorID(GameDocument& rDocument, int playerNo)
		{
			auto* pLevelInfo = rDocument.GetService<CLevelInfo>();
			return pLevelInfo->GetPlayerID(playerNo);
		}

		static int GetPlayerNo(GameDocument& rDocument, uint actorID)
		{
			auto* pLevelInfo = rDocument.GetService<CLevelInfo>();
			return pLevelInfo->GetPlayerNo(actorID);
		}

		static xgame::PlayerInformation* GetPlayerInformation(GameDocument& in_rDocument, int in_playerNo)
		{
			auto* pLevelInfo = in_rDocument.GetService<CLevelInfo>();
			if (in_playerNo < 0 || pLevelInfo->GetNumPlayers() <= in_playerNo)
				return { nullptr };

			return in_rDocument.GetService<xgame::Blackboard>()->GetPlayerInformation(in_playerNo);
		}

		static void SetPropertyLockonTarget(GameObject* pObject)
		{
			pObject->SetProperty(0x4002, { 1 });
		}

		static void SetupCollisionFilter(EFilter filter, game::ColliShapeCInfo& rInfo)
		{
			switch (filter)
			{
			case eFilter_Unk1:
				rInfo.m_Unk7 = 18;
				rInfo.m_Unk8 = 0xB0000;
				break;
			case eFilter_Unk2:
				rInfo.m_Unk7 = 18;
				rInfo.m_Unk8 = 0x40000;
				break;
			case eFilter_Unk3:
			case eFilter_Unk4:
				rInfo.m_Unk7 = 18;
				rInfo.m_Unk8 = 0x80000;
				break;
			case eFilter_Unk5:
				rInfo.m_Unk7 = 18;
				rInfo.m_Unk8 = 0x5F0000;
				break;
			case eFilter_Unk6:
				rInfo.m_Unk7 = 25;
				rInfo.m_Unk8 = 0x30000;
				break;
			case eFilter_Unk7:
				rInfo.m_Unk7 = 25;
				rInfo.m_Unk8 = 0x800000;
				break;
			case eFilter_Unk8:
				rInfo.m_Unk7 = 22;
				rInfo.m_Unk8 = 0x30000;
				break;
			case eFilter_Unk9:
			case eFilter_Unk10:
				rInfo.m_Unk7 = 19;
				rInfo.m_Unk8 = 0x30000;
				break;
			case eFilter_Unk11:
				rInfo.m_Unk7 = 16;
				rInfo.m_Unk8 = 0x4C0000;
				break;
			case eFilter_Unk12:
				rInfo.m_Unk7 = 20;
				rInfo.m_Unk8 = 0x200000;
				break;
			case eFilter_Unk13:
				rInfo.m_Unk7 = 21;
				rInfo.m_Unk8 = 0;
				break;
			case eFilter_Unk14:
				rInfo.m_Unk7 = 16;
				rInfo.m_Unk8 = 0x5F0000;
				break;
			case eFilter_Unk15:
				rInfo.m_Unk7 = 16;
				rInfo.m_Unk8 = 0xE0000;
				break;
			case eFilter_Unk16:
				rInfo.m_Unk7 = 29;
				rInfo.m_Unk8 = 0x540000;
				break;
			case eFilter_Unk17:
				rInfo.m_Unk7 = 17;
				rInfo.m_Unk8 = 0x5F0000;
				break;
			default:
				rInfo.m_Unk7 = 18;
				rInfo.m_Unk8 = 0x30000;
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

		static bool SendMessageImmToPlayer(const GameObject& in_rObj, int playerNo, fnd::Message& in_rMsg)
		{
			auto* pDocument = in_rObj.GetDocument();
			uint actorID = ObjUtil::GetPlayerActorID(*pDocument, playerNo);
			return in_rObj.SendMessageImm(actorID, in_rMsg);
		}

		static bool SendMessageImmToPlayer(const GameObject& in_rObj, fnd::Message& in_rMsg)
		{
			return SendMessageImmToPlayer(in_rObj, 0, in_rMsg);
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

			return in_rObject.SendMessageImm(pLevelInfo->m_Cameras[in_playerNo], in_rMessage);
		}

		static bool SendMessageImmToCamera(GameObject& in_rObject, fnd::Message& in_rMessage)
		{
			return SendMessageImmToCamera(in_rObject, 0, in_rMessage);
		}

		static void SendMessageToSetObject(const GameObject& rObj, const CSetObjectID& id, fnd::Message& rMsg, bool create)
		{
			auto* pDocument = rObj.GetDocument();
			auto* pSetMgr = pDocument->GetService<CSetObjectManager>();
			pSetMgr->SendObjectMessage(id, rMsg, rObj.GetID(), create);
		}

		static bool SendMessageImmToSetObject(const GameObject& rObj, const CSetObjectID& id, fnd::Message& rMsg, bool create)
		{
			auto* pDocument = rObj.GetDocument();
			auto* pSetMgr = pDocument->GetService<CSetObjectManager>();
			if (!pSetMgr)
				return false;

			return pSetMgr->SendObjectMessageImm(id, rMsg, rObj.GetID(), create);
		}

		static GameObjectHandle<CSetObjectListener> GetGameObjectHandle(const GameDocument& rDoc, const CSetObjectID& id, size_t unit)
		{
			auto* pSetMan = rDoc.GetService<CSetObjectManager>();
			if (!pSetMan)
				return nullptr;
			
			ut::RefPtr<CSetObject> setObj{};
			pSetMan->GetSetObjectFromUniqID(setObj, id.Value);
			if (!setObj)
			{
				return nullptr;
			}

			return setObj->GetNthObject(unit);
		}

		static GameObjectHandle<CSetObjectListener> GetGameObjectHandle(const GameDocument& rDoc, const CSetObjectID& id)
		{
			return GetGameObjectHandle(rDoc, id, 0);
		}

		static bool GetSetObjectTransform(const GameDocument& rDoc, const CSetObjectID& id, csl::math::Vector3* pPosition, csl::math::Quaternion* pRotation)
		{
			auto* pObjMan = rDoc.GetService<CSetObjectManager>();
			if (!pObjMan)
				return false;

			auto resObj = pObjMan->GetResObjectByID(id);
			if (!resObj)
				return false;

			auto unit = resObj.GetUnit(0);
			if (!unit.IsValid())
				return false;
			
			if (pPosition)
				*pPosition = unit.GetPosition();
		
			if (pRotation)
				*pRotation = SetEd::CalcRotationByAngle(unit.GetRotation());

			return true;
		}

		static GameObjectHandle<CSetObjectListener> CreateSetObject(const GameDocument& rDoc, const CSetObjectID& id)
		{
			auto* pObjMan = rDoc.GetService<CSetObjectManager>();
			if (!pObjMan)
				return nullptr;

			return pObjMan->CreateObjectBySetObjectID(id);
		}

		static void AddScore(GameObject& in_rGameObject, const char* in_pName, xgame::MsgDamageBase& in_rMessage, csl::math::Vector3& in_rPosition)
		{
			if (in_rMessage.PlayerNo < 0)
				return;
		
			xgame::MsgScore msgScore{};
			msgScore.m_pName = in_pName;
			msgScore.m_Position = in_rPosition;
			msgScore.m_PlayerNo = in_rMessage.PlayerNo;
			msgScore.m_BonusData = in_rMessage.m_Bonus;

			in_rGameObject.SendMessageImm(in_rGameObject.GetDocument()->GetGameActorID(), msgScore);
		}

		static void AddScore(GameObject& in_rGameObject, const char* in_pName, int in_playerNo, const csl::math::Vector3& in_rPosition)
		{
			if (in_playerNo < 0)
				return;

			xgame::MsgScore msg{};
			msg.m_pName = in_pName;
			msg.m_Position = in_rPosition;
			msg.m_PlayerNo = in_playerNo;

			in_rGameObject.SendMessageImm(in_rGameObject.GetDocument()->GetGameActorID(), msg);
		}

		static void AddScore(GameObject& in_rGameObject, const char* in_pName, xgame::MsgDamageBase& in_rMessage)
		{
			auto position = in_rGameObject.GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.GetTranslation();
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
			msg.m_pName = in_pName;
			msg.m_Position = pTransform->m_Frame.m_Unk3.GetTranslation();
			msg.m_PlayerNo = in_playerNo;
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

		static fnd::SoundHandle PlaySE(const char* in_pSoundName, const csl::math::Vector3& in_rPosition, fnd::SoundDeviceTag device)
		{
			auto* pSoundManager = csl::fnd::Singleton<fnd::SoundPlayer>::GetInstance();
			if (!pSoundManager)
				return { nullptr };

			fnd::SoundParam param{};
			param.m_TweenFactor = 0.0f;
			param.m_Device = device;

			return pSoundManager->Play3D(2, in_pSoundName, in_rPosition, param);
		}

		static fnd::SoundHandle PlaySE2D(const char* in_pSoundName, fnd::SoundDeviceTag device)
		{
			auto* pSoundManager = csl::fnd::Singleton<fnd::SoundPlayer>::GetInstance();
			if (!pSoundManager)
				return { nullptr };

			fnd::SoundParam param{};
			param.m_TweenFactor = 0.0f;
			param.m_Device = device;

			return pSoundManager->Play(2, in_pSoundName, param);
		}

		static bool CheckShapeUserID(const game::ColliShape* in_pShape, uint in_id)
		{
			if (!in_pShape)
				return false;

			return in_pShape->m_ID == in_id;
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

			csl::math::Vector3 Unk1{};
			csl::math::Vector3 Unk2{};
			csl::math::Vector3 Unk3{};
			float Unk4{};
			game::PathEvaluator Path{};
			fnd::HFrame* pFrame{};
			csl::ut::Bitset<uint> Flags{};
	 
		private:
			inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x0073E410), LayoutCylinder*, const Description&);
			inline static FUNCTION_PTR(math::Transform*, __thiscall, ms_fpCalcTransform, ASLR(0x0073E520), LayoutCylinder*, math::Transform*, const csl::math::Vector3&);

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