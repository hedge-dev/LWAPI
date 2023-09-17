#pragma once

namespace app
{
	class ObjZeldaPopupItemGenerator : public CSetObjectListener
	{
	private:
		inline static const size_t ms_ShapeCount = 1;
		inline static const ZeldaPopupItemType ms_ItemPool[] =
		{ ZeldaPopupItemType::eZeldaPopupItemType_RupeeGreen, ZeldaPopupItemType::eZeldaPopupItemType_RupeeBlue,
			ZeldaPopupItemType::eZeldaPopupItemType_RupeeRed, ZeldaPopupItemType::eZeldaPopupItemType_Heart };

	public:
		ZeldaPopupItemType CreateItem{};
		
		ObjZeldaPopupItemGenerator() : CSetObjectListener()
		{

		}

		void AddCallback(GameDocument& in_rDocument) override
		{
			fnd::GOComponent::Create<game::GOCCollider>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SZeldaPopupItemGeneratorParam>();
			CreateItem = ms_ItemPool[pParam->CreateItem];

			if (auto* pCollider = GetComponent<game::GOCCollider>())
			{
				pCollider->Setup({ ms_ShapeCount });

				game::ColliSphereShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Sphere;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_Unk2 |= 1;
				collisionInfo.m_Radius = pParam->ColliRadius;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk6, collisionInfo);
				pCollider->CreateShape(collisionInfo);
			}

			fnd::GOComponent::EndSetup(*this);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgHitEventCollision::MessageID:			return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
			default:												return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
		{
			size_t playerNo = ObjUtil::GetPlayerNo(*GetDocument(), in_rMessage.m_Sender);
			if (playerNo >= 0)
			{
				if (auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), playerNo))
					zelda_popupitem::CreateZeldaPopupItem(GetAllocator(), *GetDocument(), { GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx, CreateItem, playerNo});
			}

			Kill();
			SetStatusRetire();

			return true;
		}
	};
}