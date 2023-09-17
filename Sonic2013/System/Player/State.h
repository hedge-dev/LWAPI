#pragma once

namespace app::Player
{
	class CState : public ut::StateBase<CStateGOC>
	{
		csl::ut::Bitset<uint> Unk1{};
		int Unk2{};
		int Unk3{ -1 };
		float Unk4{};
		float Unk5{};
		float Unk6{};
		int Unk7{};

		void Enter(CStateGOC& in_rStateGoc, int in_unk) override
		{
			Unk1.reset();
			Unk2 = 0;
			Unk3 = -1;
			Unk6 = 0.0f;

			OnEnter(in_rStateGoc, in_unk);
		}

		void Leave(CStateGOC& in_rStateGoc, int in_unk) override
		{
			OnLeave(in_rStateGoc, in_unk);
		}

		bool Update(CStateGOC& in_rStateGoc, float in_deltaTime) override
		{
			Unk6 += in_deltaTime;
			if (Unk1.test(0))
			{
				Unk4 -= in_deltaTime;
				if (Unk4 <= 0.0f)
				{
					Unk1.reset();
					Unk1.set(1);
				}
			}

			if (!Unk1.test(2))
			{
				Transit(in_rStateGoc);
				if (Unk3 != -1)
				{
					Unk2 = Unk3;
					Unk3 = -1;
				}

				return Step(in_rStateGoc, in_deltaTime);
			}
			
			Unk5 -= in_deltaTime;
			if (Unk5 > 0.0f)
				return Step(in_rStateGoc, in_deltaTime);
		
			Unk1.reset();
			return Step(in_rStateGoc, in_deltaTime);
		}

		virtual void OnEnter(CStateGOC& in_rStateGoc, int in_unk);
		virtual void OnLeave(CStateGOC& in_rStateGoc, int in_unk);
		virtual bool Transit(CStateGOC& in_rStateGoc) { return false; }
		virtual bool Step(CStateGOC& in_rStateGoc, float in_deltaTime) { return false; }
	};
}