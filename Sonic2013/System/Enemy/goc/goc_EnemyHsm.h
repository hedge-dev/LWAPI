#pragma once

namespace app
{
	class GOCEnemyHsm : public fnd::GOComponent
	{
	public:
		struct StateDesc
		{
			int ID{};
			ut::internal::StateDescImpl* pImpl{};
		};

		struct Description
		{
			StateDesc* pStates{};
			size_t Count{};
			int DefaultStateID{};
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpOnGOCEvent, ASLR(0x00723F70), GOCEnemyHsm*, int, GameObject&, void*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x00724030), GOCEnemyHsm*, const Description&);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FE75B4));

	public:
		INSERT_PADDING(4); // boost::intrusive_ptr<ut::StateManager>
		ut::internal::HsmImpl Impl{};
		int DefaultStateID{ -1 };
		csl::ut::Bitset<byte> Unk2{};
		int Unk3{};

	public:
		GOCEnemyHsm()
		{
			unk1 = 0x1006;
			Unk2.set(0);
		}

		const char* GetFamilyID() const override
		{
			return "GOCEnemyHsm";
		}

		void Update(fnd::UpdatingPhase in_phase, const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (!Unk2.test(0) || in_phase)
				return;
		
			Impl.HSM_UPDATE(in_rUpdateInfo.DeltaTime);
		}

		void OnGOCEvent(int in_event, GameObject& in_rObject, void* in_pData) override
		{
			ms_fpOnGOCEvent(this, in_event, in_rObject, in_pData);
		}

		void Setup(const Description& in_rDescription)
		{
			ms_fpSetup(this, in_rDescription);
		}

		void SetEnableUpdate(bool in_enable)
		{
			Unk2.set(0, in_enable);
		}

		int GetCurrentStateID() const
		{
			return Impl.HSM_STATE();
		}

		bool Dispatch(fnd::Message& in_rMessage)
		{
			if (!Unk2.test(1))
				return Impl.HSM_DISPATCH(in_rMessage);

			return false;
		}

		bool ChangeState(int in_stateId)
		{
			if (Unk2.test(1) || in_stateId == Impl.HSM_STATE())
				return false;
		
			Unk2.set(1);
			Impl.SetState(in_stateId);
			Unk2.reset(1);

			return true;
		}

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
	};
}