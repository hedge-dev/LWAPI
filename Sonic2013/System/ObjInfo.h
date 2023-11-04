#pragma once

namespace app
{
	namespace fnd
	{
		class FileLoaderParam;
	}

	class CObjInfoContainer;
	class CSetObjectFactory;
	
	class CObjInfoFileLoader
	{
	public:
		virtual void Load(const char* in_pName, int in_a2) = 0;
		virtual void LoadEx(const char* in_pName, const fnd::FileLoaderParam& in_rParams) = 0;
	};
	
	class CObjInfo : public fnd::ReferencedObject
	{
		friend CObjInfoContainer;
		friend CSetObjectFactory;

	protected:
		csl::ut::Bitset<unsigned int> m_Status{};

		virtual void Load(CObjInfoFileLoader& in_rLoader) {}
		virtual void Initialize(GameDocument& in_rDocument) {}
		virtual void Finalize() {}

	public:
		virtual const char* GetInfoName() = 0;

	protected:
		virtual void RegisterCallback(CObjInfoContainer& in_rContainer) {}
	};
}