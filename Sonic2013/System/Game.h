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
		enum EPhantomType
		{
			PHANTOM_DRILL,
			PHANTOM_LASER,
			PHANTOM_ROCKET,
			PHANTOM_EAGLE,
			PHANTOM_ASTEROID,
			PHANTOM_RHYTHM,
			PHANTOM_BOMB,
			PHANTOM_HOVER,
			PHANTOM_QUAKE,
			PHANTOM_MAX
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
		void* m_Unk1;
		CGameSequence* m_pSequence;
		void* m_Unk2;
		void* m_Unk3;
		float m_AspectRatio{ 1.7777778f };
		
	public:
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