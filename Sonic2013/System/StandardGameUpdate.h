#pragma once

namespace app
{
	namespace dbg
	{
		class ProfileNode;
	}

	class CShadowManager;
	class CEffectManager;
	class SnowBallTrackManager;
	class StandardGameUpdate : public fnd::GameDocumentListener
	{
	public:
		struct Input
		{
			uint m_UpdateCategories{ static_cast<uint>(-1) };
			bool m_CustomTime{ false };
			uint m_Unk1{};
			float m_Speed{};
			bool m_Debug{};
		};

		GameDocument* m_pDocument{};
		CPhysicsWorld* m_pPhysicsWorld{};
		uint m_Unk1{};
		CSetObjectManager* m_pObjectMan{};
		FootPrintManager* m_pFootPrintMan{};
		SnowBallTrackManager* m_pSnowBallTrackMan{};
		CEffectManager* m_pEffectMan{};
		uint m_Unk2{};
		csl::ut::MoveArray<dbg::ProfileNode*> m_PerformanceNodes[4];

		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00926080), StandardGameUpdate*, const Input&, const fnd::SUpdateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupSubSystems, ASLR(0x00925D70), StandardGameUpdate*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPostShutdownObjectCallback, ASLR(0x009262B0), StandardGameUpdate*, GameDocument*);

		StandardGameUpdate(GameDocument* in_pDocument) : m_pDocument(in_pDocument)
		{
			for(auto& node_array : m_PerformanceNodes)
			{
				node_array = { game::GlobalAllocator::GetAllocator(2) };
			}

			in_pDocument->AddGameDocumentListener(this);
		}

		void SetupSubSystems()
		{
			ms_fpSetupSubSystems(this);
		}

		void Update(const Input& in_input, const fnd::SUpdateInfo& in_update)
		{
			ms_fpUpdate(this, in_input, in_update);
		}

		void PostShutdownObjectCallback(GameDocument* in_pDocument) override
		{
			ms_fpPostShutdownObjectCallback(this, in_pDocument);
		}

		~StandardGameUpdate() override
		{
			if (m_pDocument)
				m_pDocument->RemoveGameDocumentListener(this);
		}
	};
}
