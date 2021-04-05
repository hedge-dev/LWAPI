#pragma once

namespace app
{
	class ObjUtil
	{
	public:
		static hh::ut::PackFile GetPackFile(const char* pName)
		{
			const auto data = csl::fnd::Singleton<fnd::ResourceManager>::GetInstance()->Get<fnd::ResRawData>(pName);
			if (!data.IsValid())
				return hh::ut::PackFile(nullptr);

			const auto pack = hh::ut::PackFile(data->GetAddress());
			return hh::ut::PackFile(pack);
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

		static GameObjectHandle<CSetObjectListener> GetGameObjectHandle(CSetObjectManager* pSetMan, const CSetObjectID& id)
		{
			ut::RefPtr<CSetObject> setObj{};
			pSetMan->GetSetObjectFromUniqID(setObj, id);
			if (!setObj)
			{
				return nullptr;
			}

			return setObj->GetNthObject(0);
		}
	};
}