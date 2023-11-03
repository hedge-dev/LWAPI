#pragma once
#pragma push_macro("RegisterClass")
#undef RegisterClass

namespace app::fnd
{
	class RflClassNameRegistry : public ReferencedObject, csl::fnd::SingletonPointer<RflClassNameRegistry>
	{
	protected:
		csl::ut::StringMap<const RflClass*> m_Classes{ GetAllocator() };

	public:
		RflClassNameRegistry()
		{

		}

		const RflClass* GetClassByName(const char* in_pName) const
		{
			auto result = m_Classes[in_pName];
			if (result == m_Classes.end())
				return nullptr;

			return result;
		}
		
		void RegisterClass(const RflClass* in_pClass)
		{
			m_Classes.insert(pClass->GetName(), in_pClass);
		}

		/// <summary>
		/// Register a list of classes, the list must be null terminated.
		/// </summary>
		/// <param name="pClasses">Pointer to class list</param>
		void RegisterList(const RflClass** in_ppClasses)
		{
			size_t i = 0;
			while (in_ppClasses[i])
			{
				RegisterClass(in_ppClasses[i]);
				i++;
			}
		}
	};

	class BuiltinTypeRegistry
	{
	public:
		static RflClassNameRegistry* GetClassNameRegistry()
		{
			return csl::fnd::Singleton<RflClassNameRegistry>::GetInstance();
		}

		static RflTypeInfoRegistry* GetTypeInfoRegistry()
		{
			return csl::fnd::Singleton<RflTypeInfoRegistry>::GetInstance();
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::RflClassNameRegistry, ASLR(0x00FD430C));
#pragma pop_macro("RegisterClass")