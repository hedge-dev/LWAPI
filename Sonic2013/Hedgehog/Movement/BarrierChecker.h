#pragma once

namespace app::game
{
	class BarrierChecker
	{
	public:
		struct Description
		{
			bool Unk1{};
			bool Unk2{};
		};

		enum UpdateStep : byte;

		ut::RefPtr<PhysicsRaycastJob> rpRaycastJob{};
		csl::math::Vector3 CheckPositionOffset{};
		csl::math::Vector3 CheckLine{ csl::math::Vector3::UnitZ() * 10.0f };
		int Filter{ 0xC992 };
		float Unk3{ 10.0f };
		csl::ut::Enum<UpdateStep, byte> Unk4[2]{};
		char Unk5{};
		char Unk6{};
		csl::ut::Bitset<byte> Unk7{};

		void SetCheckPositionOffset(const csl::math::Vector3& in_rCheckPosOffset)
		{
			CheckPositionOffset = in_rCheckPosOffset;
		}

		void SetCheckLine(const csl::math::Vector3& in_rCheckLine)
		{
			CheckLine = in_rCheckLine;
		}

		void SetCollisionFilter(size_t in_filter)
		{
			Filter = in_filter;
		}

		void ChangeCheckBarrier(const Description& in_rDescription)
		{
			Unk7.reset();
			Unk5 = 0;
			if (in_rDescription.Unk1)
			{
				Unk7.set(0);
				Unk4[Unk5] = 0;
				Unk5++;
			}

			if (in_rDescription.Unk2)
			{
				Unk7.set(1);
				Unk4[Unk5] = 1;
				Unk5++;
			}
		}
	};
}