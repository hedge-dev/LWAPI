#pragma once

namespace app::Player
{
	class CPluginStateCheckChangePhantom : public CStatePlugin
	{
	public:
		typedef int RequestResult;

		inline static const char* ms_pName = (const char*)ASLR(0x00E003B8);

		csl::ut::Bitset<uint> Unk1{};
		int Unk2{ -1 };
		int Unk3{};
		int Unk4{};

		CPluginStateCheckChangePhantom() : CStatePlugin(ms_pName)
		{

		}

		bool CheckArea(CStateGOC& in_rStateGoc, Game::EPhantomType in_type)
		{
			switch (in_type)
			{
			case app::Game::PHANTOM_DRILL:
			{
				auto* pGroundInfo = StateUtil::GetGroundInfo(in_rStateGoc);

				if (!in_rStateGoc.IsOnGround() || !pGroundInfo->IsOnGround || !PlayerUtil::IsEnablePhantomDig(pGroundInfo->Attribute))
					return false;
			
				return true;
			}
			case app::Game::PHANTOM_LASER:
			{
				return true;
			}
			case app::Game::PHANTOM_ROCKET:
			{
				if (in_rStateGoc.Is2DMode())
					return false;
			
				return true;
			}
			case app::Game::PHANTOM_ASTEROID:
			case app::Game::PHANTOM_RHYTHM:
			{
				if (!in_rStateGoc.Is2DMode())
					return false;

				return true;
			}
			case app::Game::PHANTOM_EAGLE:
			{
				if (in_rStateGoc.Is2DMode())
					return false;
			
				auto* pGravityController = in_rStateGoc.GetPhysics()->GetGravityController();

				if (!pGravityController->IsGravityTypeOuter())
					return false;

				float radius{};
				if (!pGravityController->GetInnerRadius(&radius))
					return false;

				csl::math::Vector3 center{};
				if (!pGravityController->GetCenterPosition(&center))
					return false;

				float distance{ (in_rStateGoc.GetPosition() - center).squaredNorm() };
				if (distance >= powf(in_rStateGoc.GetBlackBoard()->Unk9 + radius, 2.0f))
					return false;
			
				return true;
			}
			case app::Game::PHANTOM_HOVER:
			{
				return true;
			}
			case app::Game::PHANTOM_BOMB:
			case app::Game::PHANTOM_QUAKE:
			default:
				return true;
			}
		}

		bool CheckEnableChange(CStateGOC& in_rStateGoc, Game::EPhantomType in_type, int in_variant, RequestResult* out_pResult, int* out_pInt)
		{
			if (StateUtil::IsDead(in_rStateGoc))
				return false;
		
			if (StateUtil::IsNowPhantom(in_rStateGoc) || Unk1.test(1))
			{
				*out_pResult = 2;
				return false;
			}

			if (!in_rStateGoc.GetBlackBoard()->GetPixieParameter()->IsEnableTransform(in_type))
				return false;
		
			if ((!Unk3 || in_type == Game::EPhantomType::PHANTOM_BOMB && Unk4 && Unk3 <= 1) && CheckArea(in_rStateGoc, in_type))
			{
				MsgPLCheckPhantomStart msg{ in_type };
				in_rStateGoc.ProcessMessageToCurrentState(msg);
				switch (msg.Unk1)
				{
				case 0:
				{
					*out_pResult = 1;
					return false;
				}
				case 1:
				{
					*out_pResult = 0;
					*out_pInt = msg.Unk2;
					return true;
				}
				default:
					break;
				}
			}

			*out_pResult = -1;
			return false;
		}

		void SetRequest(CStateGOC& in_rStateGoc, Game::EPhantomType in_type, int in_variant, int in_unk1, bool in_unk2)
		{
			if (in_unk2)
			{
				in_rStateGoc.GetBlackBoard()->GetPixieParameter()->TakePixie(in_type, in_variant);
			}

			Unk2 = in_unk1;
			StateUtil::SetDisableItemAndTransformForPauseAct(in_rStateGoc, true, false);
		}

		bool ChangePhantomByItem(CStateGOC& in_rStateGoc, Game::EPhantomType in_type, int in_variant)
		{
			Game::EPhantomType stockType = StateUtil::GetStockPixieType(in_rStateGoc);
			if (stockType == in_type || stockType == static_cast<Game::EPhantomType>(-1))
			{
				int enableResult{ -1 };
				int checkMsgResult{};
				
				CheckEnableChange(in_rStateGoc, in_type, in_variant, &enableResult, &checkMsgResult);
				if (!enableResult)
				{
					SetRequest(in_rStateGoc, in_type, in_variant, checkMsgResult, true);
					Unk1.set(1, true);

					return true;
				}

				in_rStateGoc.PlaySE("sn_phantom_miss", false);
			}

			return false;
		}
	};
}