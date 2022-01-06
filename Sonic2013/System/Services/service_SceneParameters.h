#pragma once

namespace app::xgame
{
	class SceneParameters : public fnd::GameService
	{
	public:
		inline static const char* ms_pFileExtension = ".scn-cfg.xml";
		
	protected:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFEDC));
		inline static SceneParameters** ms_pInstance = reinterpret_cast<SceneParameters**>(ASLR(0x00FEFED8));
		const FxSceneData* m_pSceneData;
		csl::ut::ObjectMoveArray<FxSceneData> m_Backups{ GetAllocator() };
		void* m_Unk1{};
		
	public:
		csl::ut::VariableString m_HostPath{ GetAllocator() };

	protected:
		bool m_HasBackup{};
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadCompatible, ASLR(0x00956600), SceneParameters* pThis, game::LuaScript& rScript);
		
		SceneParameters() : GameService(0)
		{
			*ms_pInstance = this;
		}

		void Backup()
		{
			if (!m_Backups.capacity())
			{
				m_Backups.change_allocator(GetAllocator());
				m_Backups.resize(2);
			}

			m_Backups[1] = m_Backups[0];
			m_HasBackup = true;
		}

		void Restore()
		{
			if (m_HasBackup)
				m_Backups[0] = m_Backups[1];
		}

		const FxSceneData* GetSceneData() const 
		{
			return m_pSceneData;
		}

		FxSceneData* GetEditingData()
		{
			if (!m_Backups.capacity())
			{
				if (!m_pSceneData)
					return nullptr;
				
				m_Backups.change_allocator(GetAllocator());
				m_Backups.resize(2);

				if (m_pSceneData)
					m_Backups[0] = *m_pSceneData;
			}

			return &m_Backups[0];
		}

		void ApplyParameter()
		{
			auto* pRenderMan = csl::fnd::Singleton<gfx::RenderManager>::GetInstance();

			pRenderMan->SetFxParameter(m_pSceneData->items[0]);
			pRenderMan->SetFxConfig(m_pSceneData->config);
		}

		void SetData(const FxSceneData* pData)
		{
			m_pSceneData = pData;
			ApplyParameter();
		}
		
		void SetHostFilename(const char* pName)
		{
			m_HostPath.Set(pName, GetAllocator());
		}

		const FxParameter* GetParameter(const size_t i) const
		{
			if (!m_pSceneData || i >= HH_COUNT_OF(m_pSceneData->items))
				return nullptr;
			
			return &m_pSceneData->items[i];
		}

		void LoadCompatible(game::LuaScript& rScript)
		{
			ms_fpLoadCompatible(this, rScript);
		}
		
		static SceneParameters* GetInstance()
		{
			return *ms_pInstance;
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}