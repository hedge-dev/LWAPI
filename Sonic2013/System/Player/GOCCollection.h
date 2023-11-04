#pragma once
namespace app
{
	class CGOCCollectionImpl;

	class CGOComponent : public fnd::ReferencedObject
	{
		friend CGOCCollectionImpl;

	protected:
		const char* m_pID{};

	public:
		CGOComponent()
		{

		}

		virtual void Update(float in_deltaTime) {}
		virtual void Update(const fnd::SUpdateInfo& in_rUpdateInfo) {}
	};

	class CGOCCollectionImpl
	{
	protected:
		std::dummy::vector<ut::RefPtr<CGOComponent>> m_Components{}; // actually, std::vector<boost::intrusive_ptr<app::CGOComponent>>

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x00914510), CGOCCollectionImpl*, size_t);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetGOC, ASLR(0x009145C0), CGOCCollectionImpl*, CGOComponent*);

		CGOCCollectionImpl(size_t in_capacity)
		{
			ms_fpCtor(this, in_capacity);
		}

		~CGOCCollectionImpl()
		{
			for (auto& goc : m_Components)
			{
				goc->Release();
			}
		}

		void SetGOC(CGOComponent* in_pComponent)
		{
			ms_fpSetGOC(this, in_pComponent);
		}

		CGOComponent* GetGOC(const char* in_pName) const
		{
			for (auto& goc : m_Components)
			{
				if (goc->m_pID == in_pName)
					return goc.get();
			}

			return nullptr;
		}

		template<typename T>
		T* GetGOC() const
		{
			return reinterpret_cast<T*>(GetGOC(T::staticID()));
		}

		void Update(float in_deltaTime)
		{
			for (auto& goc : m_Components)
			{
				goc->Update(in_deltaTime);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo)
		{
			for (auto& goc : m_Components)
			{
				goc->Update(in_rUpdateInfo);
			}
		}
	};

	template<size_t Capacity>
	class CGOCCollection : public CGOCCollectionImpl
	{
	public:
		CGOCCollection() : CGOCCollectionImpl(Capacity)
		{

		}
	};
}