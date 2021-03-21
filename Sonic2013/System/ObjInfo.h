#pragma once

namespace app
{
	namespace fnd
	{
		class FileLoaderParam;
	}

	class CObjInfoContainer;
	
	class CObjInfoFileLoader
	{
	public:
		virtual void Load(const char* name, int a2) = 0;
		virtual void LoadEx(const char* name, const fnd::FileLoaderParam& params) = 0;
	};
	
	class CObjInfo : public fnd::ReferencedObject
	{
		friend CObjInfoContainer;
	protected:
		csl::ut::Bitset<unsigned int> status{};

		virtual void Load(CObjInfoFileLoader& loader) {}
		virtual void Initialize(GameDocument& document) {}
		virtual void Finalize() {}
		virtual const char* GetInfoName() = 0;
		virtual void RegisterCallback(CObjInfoContainer& container) {}
	};
}