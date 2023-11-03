#pragma once

namespace app
{
	namespace animal
	{
		enum AnimalType
		{
			eAnimal_Flickie,
			eAnimal_Cookie,
			eAnimal_Peckie,
			eAnimal_Pickie,
			eAnimal_Pocky,
			eAnimal_Ricky,
			eAnimal_Rocky,
			eAnimal_Max,
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
			ePhantom_Drill,
			ePhantom_Laser,
			ePhantom_Rocket,
			ePhantom_Asteroid,
			ePhantom_Eagle,
			ePhantom_Rhythm,
			ePhantom_Hover,
			ePhantom_Bomb,
			ePhantom_Quake,
			ePhantom_Max
		};

		enum EUser
		{
			
		};

		enum ERank
		{

		};

		class CRecordTime
		{
			int m_Time{};
		};
	};

	class GameBase : fnd::ReferencedObject
	{
	public:
		virtual void Config(Application& in_rApp){}
		virtual void OnSetup(Application& in_rApp){}
		virtual void OnShutdown(Application& in_rApp){}
		virtual void Tick(Application& in_rApp){}
		virtual void Draw(Application& in_rApp){}
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