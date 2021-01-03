#pragma once

namespace app::fnd
{
	class CActor;
	
	class MessageManager : ReferencedObject, csl::ut::Singleton<MessageManager>
	{
	public:
		inline static FUNCTION_PTR(CActor*, __thiscall, ms_fpGetActor, ASLR(0x0049A950), const void* This, uint id);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAdd, ASLR(0x0049A8E0), void* This, CActor* actor);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemove, ASLR(0x0049A910), void* This, CActor* actor);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddMessage, ASLR(0x0049A680), void* This, Message& msg);

		void AddMessage(Message& msg)
		{
			return ms_fpAddMessage(this, msg);
		}

		
		void Add(CActor* actor)
		{
			return ms_fpAdd(this, actor);
		}

		void Remove(CActor* actor)
		{
			return ms_fpRemove(this, actor);
		}
		
		[[nodiscard]] CActor* GetActor(uint id) const
		{
			return ms_fpGetActor(this, id);
		}
	};
}

namespace csl::ut
{
	inline app::fnd::MessageManager** Singleton<app::fnd::MessageManager>::instance = reinterpret_cast<app::fnd::MessageManager**>(0x00FD4300);
}