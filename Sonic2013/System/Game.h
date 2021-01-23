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
}