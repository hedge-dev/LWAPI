#pragma once

namespace app
{
	class ObjUtil
	{
	public:
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

		template <class T>
		static T* GetObjectInfo(GameDocument& rDocument, const char* pName)
		{
			return reinterpret_cast<T*>(rDocument.GetService<CObjInfoContainer>()->GetInfo(pName));
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

			return hh::ut::PackFile(data->GetAddress());
		}

		static hh::gfx::res::ResModel GetModelResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResModel>(pName);
		}

		static hh::gfx::res::ResSkeleton GetSkeletonResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResSkeleton>(pName);
		}

		static hh::gfx::res::ResAnimTexSrt GetTexSrtAnimationResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResAnimTexSrt>(pName);
		}

		static hh::gfx::res::ResAnimMaterial GetMaterialAnimationResource(const char* pName, hh::ut::PackFile& rPackFile)
		{
			if (!rPackFile.IsValid())
				return { nullptr };

			return rPackFile.Get<hh::gfx::res::ResAnimMaterial>(pName);
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

		static void SendMessageImmToPlayer(const GameObject& rObj, int playerNo, fnd::Message& rMsg)
		{
			auto* pDocument = rObj.GetDocument();
			uint actorID = ObjUtil::GetPlayerActorID(*pDocument, playerNo);
			rObj.SendMessageImm(actorID, rMsg);
		}

		static void SendMessageImmToSetObject(const GameObject& rObj, const CSetObjectID& id, fnd::Message& rMsg, bool create)
		{
			auto* pDocument = rObj.GetDocument();
			auto* pSetMgr = pDocument->GetService<CSetObjectManager>();
			pSetMgr->SendObjectMessageImm(id, rMsg, rObj.GetID(), create);
		}

		static void SendMessageToSetObject(const GameObject& rObj, const CSetObjectID& id, fnd::Message& rMsg, bool create)
		{
			auto* pDocument = rObj.GetDocument();
			auto* pSetMgr = pDocument->GetService<CSetObjectManager>();
			pSetMgr->SendObjectMessage(id, rMsg, rObj.GetID(), create);
		}

		static GameObjectHandle<CSetObjectListener> GetGameObjectHandle(const GameDocument& rDoc, const CSetObjectID& id, size_t unit)
		{
			auto* pSetMan = rDoc.GetService<CSetObjectManager>();
			if (!pSetMan)
				return nullptr;
			
			ut::RefPtr<CSetObject> setObj{};
			pSetMan->GetSetObjectFromUniqID(setObj, id);
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

		static void GetSetObjectTransform(const GameDocument& rDoc, const CSetObjectID& id, csl::math::Vector3* pPosition, csl::math::Quaternion* pRotation)
		{
			auto* pObjMan = rDoc.GetService<CSetObjectManager>();
			if (!pObjMan)
				return;

			auto resObj = pObjMan->GetResObjectByID(id);
			if (!resObj)
				return;

			auto unit = resObj.GetUnit(0);
			if (!unit.IsValid())
				return;
			
			if (pPosition)
				*pPosition = unit.GetPosition();
		
			if (pRotation)
				*pRotation = SetEd::CalcRotationByAngle(unit.GetRotation());
		}

		static GameObjectHandle<CSetObjectListener> CreateSetObject(const GameDocument& rDoc, const CSetObjectID& id)
		{
			auto* pObjMan = rDoc.GetService<CSetObjectManager>();
			if (!pObjMan)
				return nullptr;

			return pObjMan->CreateObjectBySetObjectID(id);
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
	};
}