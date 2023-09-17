#pragma once

namespace app::debris
{
	struct SRandomSpaceDebrisInfo : public SDebrisBaseInfo
	{
	public:
		int Unk14{ -1 };
		float Unk15{};
		float Unk16{};
		float Unk17{};
		int Unk18{};
		uint Unk19{};
		uint Unk20{};
		uint Unk21{};
		uint Unk22{};
		uint Unk23{};
		uint Unk24{};
		uint Unk25{};
		uint Unk26{};
		uint Unk27{};
		uint Unk28{};
		uint Unk29{};
		uint Unk30{};
		uint Unk31{};
		uint Unk32{};
		uint Unk33{};
		uint Unk34{};
		uint Unk35{};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetModelRes, ASLR(0x008475E0), SRandomSpaceDebrisInfo*, const ResRandomSpaceDebris&, uint);

	public:
		SRandomSpaceDebrisInfo() : SDebrisBaseInfo(0)
		{
			std::fill(&Unk19, &Unk35, 0);
		}

		void SetModelRes(const ResRandomSpaceDebris& in_rResource, uint in_count)
		{
			ms_fpSetModelRes(this, in_rResource, in_count);
		}
	};
}