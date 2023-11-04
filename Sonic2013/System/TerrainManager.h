#pragma once

namespace app
{
	class TerrainManager : public fnd::GameService
	{
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFD9C));

	public:
		csl::ut::ObjectMoveArray<app::ut::RefPtr<TerrainBase>> Terrains{ GetAllocator() }; // ObjectMoveArray<intrusive_ptr<TerrainBase>>
		TerrainParam* pParam{};
		csl::ut::Bitset<uint> Flags{};

		TerrainManager() : GameService(0)
		{

		}

		bool IsLocalVisible(uint in_flags) const
		{
			bool result{};
			uint counter{};
			for (auto& terrain : Terrains)
			{
				if (in_flags & (1 << counter))
					result |= terrain->IsVisible();

				counter++;
			}

			return result;
		}

		void SetLocalVisible(bool in_visible, uint in_flags)
		{
			uint counter{};
			for (auto& terrain : Terrains)
			{
				if (in_flags & (1 << counter))
				{
					terrain->SetVisible(in_visible);
				}

				counter++;
			}
		}

		void SetVisible(bool in_visible)
		{
			SetLocalVisible(in_visible, 3);
		}

		bool IsVisible() const
		{
			return IsLocalVisible(3);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}