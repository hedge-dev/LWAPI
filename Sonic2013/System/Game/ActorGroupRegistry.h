#pragma once

namespace app::game
{
	struct InternalActorGroupInfo
	{
		const char* m_pName;
		size_t m_ID;
	};
	
	struct ActorGroupInfo : public InternalActorGroupInfo { };
	
	class ActorGroupRegistry : public fnd::ReferencedObject, csl::fnd::SingletonPointer<ActorGroupRegistry>
	{
	protected:
		csl::ut::StringMap<const ActorGroupInfo*> m_Groups{ GetAllocator() };

	public:
		ActorGroupRegistry()
		{
			
		}

		const ActorGroupInfo* GetInfoByName(const char* pName)
		{
			auto result = m_Groups[pName];

			if (!result.get())
				return nullptr;
			
			return result;
		}
	};
}

DEFINE_SINGLETONPTR(app::game::ActorGroupRegistry, ASLR(0x00FD7BD8))