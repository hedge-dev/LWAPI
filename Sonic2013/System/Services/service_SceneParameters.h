#pragma once

namespace app::xgame
{
	class SceneParameters : public fnd::GameService
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadCompatible, ASLR(0x00956600), SceneParameters*, game::LuaScript&);
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFEDC));
		inline static SceneParameters** ms_pInstance = reinterpret_cast<SceneParameters**>(ASLR(0x00FEFED8));

	public:
		inline static const char* ms_pFileExtension = ".scn-cfg.xml";
		
	protected:
		const FxSceneData* m_pSceneData;
		csl::ut::ObjectMoveArray<FxSceneData> m_Backups{ GetAllocator() };
		void* m_Unk1{};
		
	public:
		csl::ut::VariableString HostPath{ GetAllocator() };

	protected:
		bool m_HasBackup{};

	public:
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

		const bool& HasBackup() const
		{
			return m_HasBackup;
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

		void SetData(const FxSceneData* in_pData)
		{
			m_pSceneData = in_pData;
			ApplyParameter();
		}
		
		void SetHostFilename(const char* in_pName)
		{
			HostPath.Set(in_pName, GetAllocator());
		}

		const FxParameter* GetParameter(const size_t in_index) const
		{
			if (!m_pSceneData || in_index >= HH_COUNT_OF(m_pSceneData->items))
				return nullptr;
			
			return &m_pSceneData->items[in_index];
		}

		void LoadCompatible(game::LuaScript& in_rScript)
		{
			ms_fpLoadCompatible(this, in_rScript);
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