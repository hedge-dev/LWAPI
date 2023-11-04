#pragma once

namespace app::fnd
{
	class GameServiceTypeRegistry : public ReferencedObject, public csl::fnd::SingletonPointer<GameServiceTypeRegistry>
	{
	protected:
		csl::ut::MoveArray<const GameServiceClass*> m_Classes{ GetAllocator() };
		
	public:
		[[nodiscard]] const GameServiceClass* GetClassByName(const char* in_pName) const
		{
			for (const auto& cls : m_Classes)
			{
				const char* pName = cls->GetName();
				if (!strcmp(in_pName, pName))
				{
					return cls;
				}
			}
			
			return nullptr;
		}

		void AddService(const GameServiceClass& in_rClass)
		{
			m_Classes.push_back(&in_rClass);
		}
	};
}


DEFINE_SINGLETONPTR(app::fnd::GameServiceTypeRegistry, ASLR(0x00FD4318));