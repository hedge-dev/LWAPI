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

			auto pack = hh::ut::PackFile(data->GetAddress());
			return hh::ut::PackFile(pack);
		}
	};
}