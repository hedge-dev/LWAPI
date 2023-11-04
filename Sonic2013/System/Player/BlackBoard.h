#pragma once

namespace app::game
{
	class GravityField;
	class PathComponent;
}

namespace app::xgame
{
	class PlayerInformation : fnd::ReferencedObject
	{
	public:
		csl::math::Vector3 Position{};
		csl::math::Quaternion Rotation{};
		csl::math::Vector3 Velocity{};
		csl::math::Vector3 Unk4{};
		csl::math::Vector3 Unk5{};
		csl::math::Vector3 MtxFront{};
		csl::math::Vector3 MtxUp{};
		csl::math::Vector3 MtxRight{};
		csl::math::Vector3 GravityDirection{};
		csl::math::Vector3 Unk10{};
		csl::math::Vector3 Unk11{};
		csl::math::Vector3 Unk12{};
		csl::math::Vector3 Unk13{};
		csl::math::Vector3 Unk14{};
		csl::math::Vector3 Unk15{};
		csl::math::Vector3 Unk16{};
		csl::math::Vector3 UpVector{};
		int CameraId;
		int Unk51;
		int Unk52;
		int Unk53;
		csl::math::Vector3 Unk19{};
		float Unk20{};
		bool IsOnGround{};
		bool IsLandOnMovableGround{};
		void* Unk23{};
		csl::math::Vector3 Unk24{};
		int PixieNo{};
		bool Unk26{};
		bool Unk27{};
		char Unk28{};
		char Unk29{};
		char Unk30{};
		char Unk31{};
		char Unk50{};
		char Unk32{};
		char Unk33{};
		char Unk34{};
		char Unk35{};
		char Unk36{};
		char Unk37{};
		char Unk38{};
		bool IsTimerDisabled{};
		bool IsAttack{};
		char Unk41{};
		char Unk42{};
		char Unk43{};
		char Unk44{};
		char Unk45{};
		char Unk46{};
		char Unk47{};
		char Unk48{};
		fnd::Handle<game::PathComponent> PathComponents[4]{};
		float Unk49[4]{};
		fnd::Handle<game::GravityField> GravityField{};
		fnd::Handle<game::PathComponent> PathComponent{};
		float PathDistance{};

		void SetGravityField(game::GravityField* in_pGravityField)
		{
			sizeof(PlayerInformation);
			GravityField = in_pGravityField;
		}
	};

	class Blackboard : public fnd::GameService
	{
	private: 
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFEC4));

	public:
		PlayerInformation* pPlayerInfos[2]{};

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		PlayerInformation* GetPlayerInformation(int in_playerNo)
		{
			return pPlayerInfos[in_playerNo];
		}
	};
}

namespace app::Player
{
	typedef int EStatusFlag;

	inline static float PhantomValues[9] = { 20.0f, 0.5f, 10.0f, 10.0f , 10.0f , 10.0f , 10.0f , 10.0f , 10.0f };

	struct SPhantomData
	{
		float Unk1{};
		int Unk2{};
	};

	class CParameterPixie
	{
	public:
		INSERT_PADDING(2);
		short Unk1{};
		INSERT_PADDING(4);
		float Energy{};
		float Unk3{};
		Game::EPhantomType Type{ static_cast<Game::EPhantomType>(-1) };
		Game::EPhantomType PixieNo{ static_cast<Game::EPhantomType>(-1) };
		int Variant{};
		int Unk7{};
		csl::ut::FixedArray<SPhantomData, 9> PhantomData{};
		csl::ut::Bitset<uint> Unk8{};
		char Unk9{};

		void InitPhantomInfo(const csl::ut::MoveArray<Game::EPhantomType>& in_rPhantoms)
		{
			for (size_t i = 0; i < 9; i++)
			{
				PhantomData[i].Unk1 = PhantomValues[1];
			}

			for (size_t i = 0; i < in_rPhantoms.size(); i++)
			{
				if (in_rPhantoms[i] < Game::EPhantomType::ePhantom_Max)
				{
					PhantomData[in_rPhantoms[i]].Unk2 = 1;
				}
			}
		}

		CParameterPixie(const csl::ut::MoveArray<Game::EPhantomType>& in_rPhantoms)
		{
			InitPhantomInfo(in_rPhantoms);
		}

		virtual ~CParameterPixie() {}

		bool IsEnableTransform(Game::EPhantomType in_type) const
		{
			if (in_type >= Game::EPhantomType::ePhantom_Max)
				return false;
		
			return PhantomData[in_type].Unk2;
		}

		bool TakePixie(Game::EPhantomType in_type, int in_variant)
		{
			if (Type == in_type || Unk8.test(0) || !IsEnableTransform(in_type))
				return false;
		
			Type = in_type;
			Variant = in_variant;
			
			return true;
		}

		bool HasPixie() const
		{
			return Type != static_cast<Game::EPhantomType>(-1);
		}
	};

	class CParameterRing
	{
	private:
		int m_RingCount;

	public:
		int GetRingCount() const
		{
			return m_RingCount;
		}

		void AddNum(int in_ringNum)
		{
			m_RingCount = csl::math::Clamp<int>(m_RingCount + in_ringNum, 0, 9999);
		}

		void SetNum(int in_ringNum)
		{
			m_RingCount = csl::math::Clamp<int>(in_ringNum, 0, 9999);
		}
	};

	class CAttackStatus
	{
	public:
		int Unk1{};
		uint Type{};
		uint AttackPower{};
		uint DefensePower{};
		csl::ut::Bitset<uint> Unk5{};
		
		uint GetAttackTypeFlag() const
		{
			if (Unk5.test(2) || Unk5.test(1))
			{
				return Type | 0x400008;
			}
			else
			{
				return Type;
			}
		}

		uint GetAttackPower() const
		{
			if (Unk5.test(2) || Unk5.test(1))
			{
				return 20;
			}
			else
			{
				return AttackPower;
			}
		}

		uint GetDefensePower() const
		{
			if (Unk5.test(2) || Unk5.test(1))
			{
				return 20;
			}
			else
			{
				return DefensePower;
			}
		}

		bool IsAttack() const
		{
			return AttackType::Any(GetAttackTypeFlag());
		}

		void SetInvincible(bool in_enable, bool in_unk)
		{
			Unk5.set(in_unk, in_enable);
		}
	};

	class CBlackBoard : public fnd::ReferencedObject
	{
	public:
		csl::ut::Bitset<int> Unk1[4]{};
		int Unk2{};
		int Unk3{};
		size_t PlayerNo{};
		CParameterRing* pRingParameter{};
		CParameterPixie* pPixieParameter{};
		CAttackStatus* pAttackStatus{};
		csl::ut::Bitset<uint> Unk6{};
		float Unk7{};
		float Unk8{};
		float Unk9{};
		int Unk5{};

		CParameterRing* GetRingParameter()
		{
			return pRingParameter;
		}

		CParameterPixie* GetPixieParameter()
		{
			return pPixieParameter;
		}

		CAttackStatus* GetAttackStatus()
		{
			return pAttackStatus;
		}

		void SetStatus(EStatusFlag in_statusFlag, bool in_enable)
		{
			Unk1[3].set(in_statusFlag, in_enable);
		}
	};
}