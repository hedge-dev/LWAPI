#pragma once

namespace app::fnd
{
	class GameServiceTypeRegistry : public ReferencedObject, csl::fnd::SingletonPointer<GameServiceTypeRegistry>
	{
	protected:
		csl::ut::MoveArray<const GameServiceClass*> classes{ GetAllocator() };
		
	public:
		[[nodiscard]] const GameServiceClass* GetClassByName(const char* name) const
		{
			for (auto** it = classes.begin(); it != classes.end(); it++)
			{
				const auto* nam = (*it)->GetName();
				if (!strcmp(name, nam))
				{
					return *it;
				}
			}
			
			return nullptr;
		}
	};
}


DEFINE_SINGLETONPTR(app::fnd::GameServiceTypeRegistry, ASLR(0x00FD4318));