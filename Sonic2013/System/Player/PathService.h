#pragma once

namespace app::Player
{
	class CPlayer;

	typedef uint PathType;

	class CPathService
	{
	public:
		CPlayer* pPlayer{};
		csl::ut::Bitset<uint> Unk1{};
		game::PathEvaluator Paths[4]{};
		int Unk2{};

		virtual ~CPathService() { }

		game::PathManager* GetPathManager();

		game::PathEvaluator* GetPathEvaluator(PathType in_type)
		{
			if (Paths[in_type].Component.IsValid())
			{
				return &Paths[in_type];
			}

			return { nullptr };
		}

		void ReleasePath(PathType in_type)
		{
			Paths[in_type].Reset();
		}

		void SetPath(PathType in_type, game::PathComponent* pComponent, float distance)
		{
			if (!pComponent)
				return;
		
			Paths[in_type].SetPathObject(pComponent);
			Paths[in_type].SetDistance(distance);
		}

		game::PathComponent* Search2DPath(const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, float* out_pUnk)
		{
			game::PathRaycastInput input{};
			game::PathRaycastOutput output{};
			
			input.From = in_rFrom;
			input.To = in_rTo;
			input.Unk1 = 1;
			input.Unk2 = 1;

			if (GetPathManager()->CastRay(input, &output))
			{
				if (out_pUnk)
					*out_pUnk = output.Distance;
			}

			return output.pComponent;
		}
	};
}