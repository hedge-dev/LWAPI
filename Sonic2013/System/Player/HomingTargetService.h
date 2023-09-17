#pragma once

namespace app::Player
{
	class CPlayer;

	class CHomingTargetService
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpHitCollision, ASLR(0x0085EEB0), CHomingTargetService*, const game::ColliShape*, const game::ColliShape*);

	public:
		class TargetData
		{
		public:
			void* Unk1{};
			char Unk2{};
			char Unk3{};
			csl::ut::Bitset<ushort> Unk4{};
			fnd::Handle<game::ColliShape> Unk5{};
			GameObjectHandle<GameObject> Unk6{};
			csl::math::Vector3 Unk7{};
			float Unk8{};
			float Unk9{};
			float Unk10{};
			float Unk11{};
			csl::ut::FixedArray<int, 3> Unk12{};

			TargetData()
			{
				Unk12.assign(-1);
			}

			bool IsInvalid() const
			{
				return !Unk5.Get();
			}
			
			game::ColliShape* GetShape() const
			{
				if (!IsInvalid())
					return Unk5.Get();

				return { nullptr };
			}
		};

		enum EMode
		{

		};

		CPlayer* pPlayer{};
		int Unk1{};
		csl::ut::Bitset<byte> Unk2{};
		csl::ut::Enum<EMode, byte> Mode{};
		csl::ut::Enum<Game::EUser, byte> User{};
		csl::ut::ObjectMoveArray<TargetData> Targets{ GameObject::GetAllocator() };
		csl::ut::MoveArray<fnd::Handle<game::ColliShape>> Unk3{ GameObject::GetAllocator() };
		csl::ut::MoveArray<fnd::Handle<game::ColliShape>> Unk4{ GameObject::GetAllocator() };
		ut::RefPtr<game::PhysicsRaycastJob> rpRaycastJob{};
		int Unk5{};
		float Unk6{};
		csl::math::Matrix34 Unk7{};
		csl::math::Matrix34 Unk8{};
		INSERT_PADDING(16);
		csl::math::Plane Unk9[6]{};
		INSERT_PADDING(16);
		int Unk10{};

		CHomingTargetService(CPlayer* in_pPlayer, Game::EUser in_user)
		{
			/*Targets.reserve(6);
			Unk3.reserve(20);
			Unk4.reserve(6);

			rpRaycastJob = new(GameObject::GetAllocator()) game::PhysicsRaycastJob();
			rpRaycastJob->Reserve(18);

			csl::math::Matrix34 positionMatrix{ 0.0f, 4.3f, 0.0f };
			csl::math::Matrix34 rotationMatrix{ 'x', 0.0f };
			csl::math::Matrix34 positionOffsetMatrix{ 0.0f, 0.0f, -55.0f };

			rotationMatrix.addTo(positionMatrix);
			positionOffsetMatrix.addTo(positionMatrix);

			Unk7 = positionMatrix;*/
		}

		virtual ~CHomingTargetService() { }

		const TargetData* GetFirstTarget() const
		{
			TargetData target{};

			if (Targets.empty() || (target = Targets[0], target.IsInvalid()))
			{
				return { nullptr };
			}
			else
			{
				return &Targets[0];
			}
		}

		void HitCollision(const game::ColliShape* in_pSelf, const game::ColliShape* in_pOther)
		{
			ms_fpHitCollision(this, in_pSelf, in_pOther);
		}
	};
}