#pragma once

namespace app::ut::internal
{
	class HsmImpl
	{
	private:
		inline static FUNCTION_PTR(int, __thiscall, ms_fpHSM_STATE, ASLR(0x009233B0), const HsmImpl*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpHSM_UPDATE, ASLR(0x009233D0), HsmImpl*, float);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpHSM_DISPATCH, ASLR(0x00923420), HsmImpl*, fnd::Message&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpHSM_TRAN, ASLR(0x009237F0), HsmImpl*, int);

	public:
		int Unk1{ -1 };
		int Unk2{};
		int Unk3{};
		INSERT_PADDING(4) {}; // boost::intrusive_ptr<app::ut::internal::StateManagerImpl>
		int Unk4{};
		INSERT_PADDING(20) {}; // boost::intrusive_ptr<app::ut::internal::StateImpl>[5]

		int HSM_STATE() const
		{
			return ms_fpHSM_STATE(this);
		}

		void HSM_UPDATE(float in_deltaTime)
		{
			ms_fpHSM_UPDATE(this, in_deltaTime);
		}

		bool HSM_DISPATCH(fnd::Message& in_rMessage)
		{
			return ms_fpHSM_DISPATCH(this, in_rMessage);
		}

		void HSM_TRAN(int in_stateId)
		{
			return ms_fpHSM_TRAN(this, in_stateId);
		}

		void SetState(int in_stateId)
		{
			Unk3 = Unk2;
			HSM_TRAN(in_stateId);
		}
	};
}