#pragma once

namespace app
{
	typedef size_t CSetObjectID;
	
	class CSetObjectManager : public fnd::GameService
	{
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEF2E8));
	protected:
		INSERT_PADDING(1076){};
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSendObjectMessageImpl, ASLR(0x0084CBA0), CSetObjectManager*, CSetObjectID, fnd::Message&, uint sender, bool create, bool immediate);
		inline static FUNCTION_PTR(CSetObjectListener*, __thiscall, ms_fpGetSetObjectFromUniqID, ASLR(0x0084C830), CSetObjectManager*, size_t);

		void SendObjectMessageImpl(CSetObjectID id, fnd::Message& rMsg, uint sender, bool create, bool immediate)
		{
			ms_fpSendObjectMessageImpl(this, id, rMsg, sender, create, immediate);
		}

	public:
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		CSetObjectListener* GetSetObjectFromUniqID(size_t id)
		{
			return ms_fpGetSetObjectFromUniqID(this, id);
		}
		
		void SendObjectMessage(CSetObjectID id, fnd::Message& rMsg, uint sender, bool create)
		{
			SendObjectMessageImpl(id, rMsg, sender, create, false);
		}
		
		void SendObjectMessageImm(CSetObjectID id, fnd::Message& rMsg, uint sender, bool create)
		{
			SendObjectMessageImpl(id, rMsg, sender, create, true);
		}
	};
}