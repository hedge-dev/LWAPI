#pragma once

namespace app::fnd
{
	class GameServiceTypeRegistry : public ReferencedObject, csl::ut::Singleton<GameServiceTypeRegistry>
	{
	protected:
		csl::ut::MoveArray<GameServiceClass*> classes{ allocator };
		
	public:
		[[nodiscard]] GameServiceClass* GetClassByName(const char* name) const
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

namespace csl::ut
{
	inline app::fnd::GameServiceTypeRegistry** Singleton<app::fnd::GameServiceTypeRegistry>::instance = reinterpret_cast<
		app::fnd::GameServiceTypeRegistry**>(ASLR(0x00FD4318));
}