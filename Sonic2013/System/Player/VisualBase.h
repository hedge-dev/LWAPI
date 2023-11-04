#pragma once

namespace app::Player
{
	class CVisualGOC;
	class GOCReferenceHolder;
	class CPlayer;
	class EffectList;
	class CVisualUnit;

	class CVisualBase
	{
	public:
		CPlayer* pPlayer{};
		CVisualGOC* pVisualGoc{};
		game::GOCSound* pSoundGoc{};

	public:
		CVisualBase(CPlayer* in_pPlayer, CVisualGOC* in_pVisualGoc) : pPlayer(in_pPlayer), pVisualGoc(in_pVisualGoc), pSoundGoc(in_pPlayer->GetComponent<game::GOCSound>())
		{
			
		}

		Game::EUser GetUser()
		{
			return pVisualGoc->User;
		}

		CPhysics* GetPhysics()
		{
			return pPlayer->rpPhysics.get();
		}

		CPhysics* GetPhysics() const
		{
			return pPlayer->rpPhysics.get();
		}

		csl::math::Vector3 GetPosition() const
		{
			return GetPhysics()->Position;
		}

		csl::math::Quaternion GetRotation() const
		{
			return GetPhysics()->Rotation;
		}

		csl::math::Matrix34& GetLocaterMatrix() const
		{
			return pVisualGoc->GetLocaterMatrix();
		}

		csl::math::Matrix34& GetPhysicsMatrix() const
		{
			return GetPhysics()->PhysicsMatrix;
		}

		csl::math::Matrix34& GetViewMatrix() const
		{
			return GetPhysics()->CameraViewMtx;
		}

		csl::math::Vector3 GetRight() const
		{
			return GetPhysics()->GetRight();
		}

		csl::math::Vector3 GetUp() const
		{
			return GetPhysics()->GetUp();
		}

		csl::math::Vector3 GetFront() const
		{
			return GetPhysics()->GetFront();
		}

		csl::math::Vector3 GetVelocity() const
		{
			return GetPhysics()->Velocity;
		}

		csl::math::Vector3 GetHorzVelocity() const
		{
			return GetPhysics()->GetHorzVelocity();
		}

		csl::math::Vector3 GetVertVelocity() const
		{
			return GetPhysics()->GetVertVelocity();
		}

		csl::math::Vector3 GetUpDirection() const
		{
			return GetPhysics()->Up;
		}

		csl::math::Vector3 GetGravityUpDirection() const
		{
			return GetPhysics()->GetGravityUpDirection();
		}

		hh::ut::ResCommon<fnd::ResRawData> GetRawData(const char* in_pName)
		{
			return csl::fnd::Singleton<fnd::ResourceManager>::GetInstance()->Get<fnd::ResRawData>(in_pName);
		}

		bool GetReflectionInfo(csl::math::Vector3* out_pUnk1, csl::math::Vector3* out_pUnk2) const
		{
			auto* pBlackboard = pPlayer->rpBlackboard.get();
			if (pBlackboard->Unk1[3].test(25))
				return false;
		
			auto* pPhysics = GetPhysics();
			if (!pPhysics->Unk9.IsOnGround)
				return false;

			if (pPhysics->Unk9.Unk7 >= 50.0f)
				return false;
		
			if ((pPhysics->Unk9.GetAttribute() & 0x200) == 0)
				return false;

			auto* pGravityController = GetPhysics()->GetGravityController();
			if (!pGravityController->IsGravityTypeRunPath())
				return false;
		
			float gravityInnerRadius{};
			if (!pGravityController->GetInnerRadius(&gravityInnerRadius))
				return false;

			csl::math::Vector3 gravityCenterPosition{};
			if (!pGravityController->GetCenterPosition(&gravityCenterPosition))
				return false;
		
			if ((pPhysics->Unk9.Unk5 - gravityCenterPosition).norm() > powf(gravityInnerRadius * 5.0f, 2.0f))
				return false;
		
			*out_pUnk1 = pPhysics->Unk9.Unk5;
			*out_pUnk2 = pPhysics->Unk9.Unk4;

			return true;
		}

		bool IsOnGround() const
		{
			return GetPhysics()->IsOnGround();
		}

		bool IsSideView() const
		{
			return pPlayer->rpBlackboard.get()->Unk2 == 1;
		}

		bool IsNowSuperSonic() const
		{
			return pPlayer->rpBlackboard.get()->Unk1[3].test(23);
		}

		bool IsLinkCostume() const
		{
			return pPlayer->rpBlackboard.get()->Unk1[3].test(31);
		}

		fnd::SoundHandle PlaySE(const char* in_pCueName)
		{
			return pSoundGoc->Play(in_pCueName, 0.0f);
		}

		void StopSE(fnd::SoundHandle in_soundHandle)
		{
			in_soundHandle.Stop(0.0f);
		}

		virtual ~CVisualBase() = default;
	};

	class CEffectBase : public fnd::ReferencedObject, public CVisualBase
	{
	public:
		int Unk1{};
		const char* pEffectName{};
		bool Unk2{};

		CEffectBase(CPlayer* in_pPlayer, CVisualGOC* in_pVisualGoc, const char* in_pEffectName) : CVisualBase(in_pPlayer, in_pVisualGoc), pEffectName(in_pEffectName), ReferencedObject()
		{

		}
	};
}