#pragma once

#define UPPER_MASK 0x80000000
#define LOWER_MASK 0x7fffffff
#define STATE_SIZE 624
#define SHIFT_SIZE 397

namespace SonicUSA::System
{
	class MtRandom
	{
	private:
		inline static const size_t ms_XorMask[] = { 0, 0x9908B0DF };

	public:
		int Mt[STATE_SIZE]{};
		int Index{};
		int Unk3{};

		virtual ~MtRandom() = default;

		void Init(size_t in_seed)
		{
			Mt[0] = in_seed;
		
			int magicNumber = 0x6C078965;
			for (size_t i = 1; i < STATE_SIZE; i++)
				Mt[i] = 0x6C078965 * (Mt[i - 1] ^ (Mt[i - 1] >> 30)) + i;

			Index = 0;
		}

		size_t Rand()
		{
			int index = 0;
			if (Index < STATE_SIZE - 1)
				index = Index + 1;

			int shiftSize = Index + SHIFT_SIZE;
			if (Index >= STATE_SIZE - SHIFT_SIZE)
				shiftSize = Index - STATE_SIZE - SHIFT_SIZE;

			int mtValue = ((Mt[Index] ^ (Mt[Index] ^ Mt[index]) & LOWER_MASK) >> 1) ^ ms_XorMask[Mt[index] & 1] ^ Mt[shiftSize];
			Mt[Index] = mtValue;
			Index = index;
			
			size_t random = (((((((mtValue >> 11) ^ mtValue) & 0xFF3A58AD) << 7) ^ (mtValue >> 11) ^ mtValue) & 0xFFFFDF8C) << 15) ^ ((((mtValue >> 11) ^ mtValue) & 0xFF3A58AD) << 7) ^ (mtValue >> 11) ^ mtValue;
			return random ^ (random >> 18);
		}
	};

	class Random
	{
	public:
		INSERT_PADDING(2500);
		MtRandom MtRand{};

		virtual ~Random() = default;

		Random()
		{
			MtRand.Init(1);
			Reset(0xBADED9A7);
		}
		
		Random(size_t in_seed)
		{
			MtRand.Init(1);
			Reset(in_seed);
		}

		void Reset(size_t in_seed)
		{
			MtRand.Init(in_seed);
		}

		size_t genrand_int32() 
		{
			return MtRand.Rand();
		}

		inline float genrand_float32()
		{
			return genrand_int32() * 2.328306436538696e-10f;
		}

		inline static Random* GetInstance()
		{
			return reinterpret_cast<SonicUSA::System::Random*>(ASLR(0x00FBC1C8));
		}
	};
}