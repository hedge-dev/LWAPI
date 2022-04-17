#pragma once

namespace app
{
	class TerrainParam;

	class TerrainBase : public fnd::ReferencedObject
	{
	public:
		TerrainParam* m_pParam;
		csl::ut::Bitset<uint> m_Flags{};

		virtual void Update(const fnd::SUpdateInfo& in_info) { }
		virtual void Load(const char*, const char*) { }
		virtual void Setup() { }
		virtual void Prepare() { }
		virtual void LoadDelay() { }
		virtual void LoadEnd() { }
		virtual void Cleanup() { }
		virtual void LevelStarted() { }
		virtual void SetVisible(bool in_visible) { m_Flags.set(0, in_visible); }
		virtual bool IsVisible() const { return m_Flags.test(0); }
		virtual bool SetVisibleModel(const char* in_pName, bool in_visible) { return false; }
		virtual game::res::ResNameExtra GetResNameExtra(const char* in_pName, bool in_visible) { return {}; }
		virtual res::ResSvCol GetResSvCol() const { return {}; };
		virtual void ChangeScene(uint in_scene) { };
		virtual void SetSceneHide(uint in_scene, bool in_hide) { };
		virtual void ResetScene() { };
		virtual void ResetFullScene(bool in_a1) { };
	};
}