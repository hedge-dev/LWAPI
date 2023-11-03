#pragma once

namespace app::fnd
{
	class DataResource : public ReferencedObject
	{
	protected:
		void* m_pObject;
		const RflClass* m_pClass;
		RflClassNameRegistry* m_pNameRegistry{ BuiltinTypeRegistry::GetClassNameRegistry() };
		RflTypeInfoRegistry* m_pTypeRegistry{ BuiltinTypeRegistry::GetTypeInfoRegistry() };

	public:
		DataResource(Variant& in_rVariant)
		{
			m_pObject = in_rVariant.pObject;
			m_pClass = in_rVariant.pClass;
		}

		~DataResource()
		{
			if (m_pObject && m_pClass)
			{
				m_pTypeRegistry->CleanupLoadedObject(m_pObject, m_pClass->GetName());
				m_pTypeRegistry->FinishLoadedObject(m_pObject, m_pClass->GetName());
			}
		}

		void* GetContentsPointer() const
		{
			return m_pObject;
		}

		template<typename T>
		T* GetContents() const
		{
			return reinterpret_cast<T*>(GetContentsPointer());
		}
		
		const RflClass* GetClass() const
		{
			return m_pClass;
		}
	};
}