#pragma once

namespace app
{
	class ObjUtil
	{
	public:
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

		static GameObjectHandle<CSetObjectListener> CreateSetObject(const GameDocument& rDoc, const CSetObjectID& id)
		{
			auto* pObjMan = rDoc.GetService<CSetObjectManager>();
			if (!pObjMan)
				return nullptr;

			return pObjMan->CreateObjectBySetObjectID(id);
		}
	};
}