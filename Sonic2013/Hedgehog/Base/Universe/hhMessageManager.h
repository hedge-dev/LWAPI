#pragma once

namespace app::fnd
{
	class CActor;
	
	class MessageManager : ReferencedObject
	{
		
	public:
		inline static MessageManager** ms_ppMessageManager = reinterpret_cast<MessageManager**>(ASLR(0x0FD4300));
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
		
		static MessageManager* GetInstance()
		{
			return *ms_ppMessageManager;
		}
	};
}