#pragma once

namespace app::game
{
	class GOCLauncher : public fnd::GOComponent
	{
	public:
		struct ShotInfo
		{
			csl::math::Vector3 Position{};
			csl::math::Vector3 Direction{};
			float OutOfControl{};
			float TravelTime{};
			INSERT_PADDING(20);
		};

	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpAdd, ASLR(0x004C1BC0), GOCLauncher*, const ShotInfo&, float, const char*);
		inline static FUNCTION_PTR(ShotInfo&, __thiscall, ms_fpGetShotInfo, ASLR(0x004C1B70), const GOCLauncher*, const char*);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7764));

		csl::math::Vector3 Gravity{};
		csl::ut::MoveArray<ShotInfo> ShotInfos{ 1, GetAllocator() };
		csl::ut::Bitset<uint8> Flags{};
		
	public:
		GOCLauncher()
		{
			m_Flags = 2;
		}

		const char* GetFamilyID() const override
		{
			return "GOCLauncher";
		}

		void OnGOCEvent(int in_event, GameObject& in_rObject, void* in_pData) override
		{
			
		}

		bool Add(const ShotInfo& in_rShotInfo, float in_Unk, const char* in_pName)
		{
			return ms_fpAdd(this, in_rShotInfo, in_Unk, in_pName);
		}

		ShotInfo& GetShotInfo(const char* in_pName) const
		{
			return ms_fpGetShotInfo(this, in_pName);
		}

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
	};
}