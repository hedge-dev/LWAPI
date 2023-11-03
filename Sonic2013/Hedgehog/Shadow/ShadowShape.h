#pragma once

namespace app
{
	enum ShadowQualityType;
}

namespace app::game
{
	class GOCShadow;

	class ShadowShapeCInfo
	{
	public:
		int Unk1{};
		int Unk2{};
		int Unk3{ -1 };
		int Unk4{};
		char Unk5{ 1 };
		csl::ut::Enum<ShadowQualityType, uint8> ShadowQuality{};

		ShadowShapeCInfo(int in_unk1) : Unk1(in_unk1)
		{
			ShadowQuality = 3;
		}
	};

	class ShadowShape : public fnd::ReferencedObject, public fnd::HFrameListener
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetMaxDownDist, ASLR(0x004CC030), ShadowShape*, float);

	public:
		csl::math::Matrix34 Unk1{};
		INSERT_PADDING(4); // boost::intrusive_ptr<CShadowObj>;
		size_t UserID{ static_cast<size_t>(-1) };
		int Unk3{};
		csl::ut::Bitset<uint8> Unk4{};
		GOCShadow* pShadowGoc{};

		void SetUserID(size_t in_userID)
		{
			UserID = in_userID;
		}

		void SetMaxDownDist(float in_maxDownDist)
		{
			ms_fpSetMaxDownDist(this, in_maxDownDist);
		}
	};
}