#pragma once

namespace app
{
	namespace animal
	{
		enum AnimalType
		{
			ANIMAL_FLICKIE,
			ANIMAL_COOKIE,
			ANIMAL_PECKIE,
			ANIMAL_PICKIE,
			ANIMAL_POCKY,
			ANIMAL_RICKY,
			ANIMAL_ROCKY,
			ANIMAL_MAX,
		};
	}
	
	class Game
	{
	public:
		enum EPlayMode
		{

		};

		enum EPhantomType
		{
			PHANTOM_DRILL,
			PHANTOM_LASER,
			PHANTOM_ROCKET,
			PHANTOM_ASTEROID,
			PHANTOM_EAGLE,
			PHANTOM_RHYTHM,
			PHANTOM_HOVER,
			PHANTOM_BOMB,
			PHANTOM_QUAKE,
			PHANTOM_MAX
		};

		enum EUser
		{
			
		};

		enum ERank
		{

		};

		class CRecordTime
		{
			int Time{};
		};
	};

	class GameBase : fnd::ReferencedObject
	{
	public:
		virtual void Config(Application& rApp){}
		virtual void OnSetup(Application& rApp){}
		virtual void OnShutdown(Application& rApp){}
		virtual void Tick(Application& rApp){}
		virtual void Draw(Application& rApp){}
	};
	
	class CGame : public GameBase, public fnd::CBranchActor
	{
	protected:
		app::ut::RefPtr<GameMode> m_rpMode;
		CGameSequence* m_pSequence;
		void* m_Unk2;
		void* m_Unk3;
		float m_AspectRatio{ 1.7777778f };
		
	public:
		void InitGameMode(GameMode* in_pMode);
		void ShutdownGameMode();

		GameMode* GetGameMode() const
		{
			return m_rpMode;
		}

		CGameSequence* GetSequence() const
		{
			return m_pSequence;
		}

		float GetAspectRatio() const
		{
			return m_AspectRatio;
		}
	};
}