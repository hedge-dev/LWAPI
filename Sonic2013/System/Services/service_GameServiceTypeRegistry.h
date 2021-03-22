#pragma once

namespace app::fnd
{
	class GameServiceTypeRegistry : public ReferencedObject, csl::fnd::SingletonPointer<GameServiceTypeRegistry>
	{
	protected:
		csl::ut::MoveArray<const GameServiceClass*> m_Classes{ GetAllocator() };
		
	public:
		[[nodiscard]] const GameServiceClass* GetClassByName(const char* name) const
		{
			for (auto& cls : m_Classes)
			{
				const auto* nam = cls->GetName();
				if (!strcmp(name, nam))
				{
					return cls;
				}
			}
			
			return nullptr;
		}

		void AddService(const GameServiceClass& rClass)
		{
			m_Classes.push_back(&rClass);
		}
	};
}


DEFINE_SINGLETONPTR(app::fnd::GameServiceTypeRegistry, ASLR(0x00FD4318));