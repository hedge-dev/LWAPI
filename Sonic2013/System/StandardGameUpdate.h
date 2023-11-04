#pragma once

namespace app
{
	namespace dbg
	{
		class ProfileNode;
	}

	class CShadowManager;
	class SnowBallTrackManager;

	class StandardGameUpdate : public fnd::GameDocumentListener
	{
	public:
		struct Input
		{
			uint UpdateCategories{ static_cast<uint>(-1) };
			bool CustomTime{ false };
			uint Unk1{};
			float Speed{};
			bool Debug{};
		};
	
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00926080), StandardGameUpdate*, const Input&, const fnd::SUpdateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupSubSystems, ASLR(0x00925D70), StandardGameUpdate*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPostShutdownObjectCallback, ASLR(0x009262B0), StandardGameUpdate*, GameDocument*);

	public:
		GameDocument* pDocument{};
		CPhysicsWorld* pPhysicsWorld{};
		uint Unk1{};
		CSetObjectManager* pObjectMan{};
		FootPrintManager* pFootPrintMan{};
		SnowBallTrackManager* pSnowBallTrackMan{};
		Effect::CEffectManager* pEffectMan{};
		uint Unk2{};
		csl::ut::MoveArray<dbg::ProfileNode*> PerformanceNodes[4];

		StandardGameUpdate(GameDocument* in_pDocument) : pDocument(in_pDocument)
		{
			for(auto& node_array : PerformanceNodes)
			{
				node_array = { game::GlobalAllocator::GetAllocator(2) };
			}

			in_pDocument->AddGameDocumentListener(this);
		}

		void SetupSubSystems()
		{
			ms_fpSetupSubSystems(this);
		}

		void Update(const Input& in_rInput, const fnd::SUpdateInfo& in_rUpdateInfo)
		{
			ms_fpUpdate(this, in_rInput, in_rUpdateInfo);
		}

		void PostShutdownObjectCallback(GameDocument* in_pDocument) override
		{
			ms_fpPostShutdownObjectCallback(this, in_pDocument);
		}

		~StandardGameUpdate() override
		{
			if (pDocument)
				pDocument->RemoveGameDocumentListener(this);
		}
	};
}
