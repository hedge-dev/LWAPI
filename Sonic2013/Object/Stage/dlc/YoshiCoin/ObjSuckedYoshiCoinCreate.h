#pragma once

namespace app::sucked_yoshi_coin
{
    inline static ObjSuckedYoshiCoin* Create(GameDocument& in_rDocument, const CreateInfo& in_rCreateInfo)
    {
        auto* pObject = new ObjSuckedYoshiCoin(in_rCreateInfo);
        if (!pObject)
            return { nullptr };

        in_rDocument.AddGameObject(pObject);
        return pObject;
    }
}