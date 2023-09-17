#pragma once

namespace app::Player::VisualUtil
{
	template <typename T>
	T* GetObjectInfo(GameDocument& in_rDocument)
	{
		return reinterpret_cast<T*>(ObjUtil::GetObjectInfo(in_rDocument, T::ms_pName));
	}
}