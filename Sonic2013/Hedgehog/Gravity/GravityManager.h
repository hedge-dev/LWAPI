#pragma once

namespace app::game
{
	class GravityDebugDraw;

	class GravityManager : public fnd::GameService
	{
	private:
		inline static FUNCTION_PTR(GravityField*, __thiscall, ms_fpfindGravityField, ASLR(0x004CE410), const GravityManager*, const csl::math::Vector3&, float, GravityField*);
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FD7C28));

	public:
		csl::ut::Bitset<uint> Flags{};
		csl::ut::LinkList<GravityField> Unk1{};
		csl::ut::LinkList<GravityField> Unk2{};
		csl::ut::LinkList<GravityPhantom> Unk3{};
		csl::ut::LinkList<GravityPhantom> Unk4{};
		csl::ut::LinkList<GravityEffect> Effects{};
		INSERT_PADDING(16);
		ut::RefPtr<ut::AabbTree> rpAabbTree{};
		ut::RefPtr<GravityDebugDraw> rpDebugDraw{};
		INSERT_PADDING(8);
		
		GravityField* findGravityField(const csl::math::Vector3& in_rPoint, float in_unk, GravityField* out_pGravityField) const
		{
			return ms_fpfindGravityField(this, in_rPoint, in_unk, out_pGravityField);
		}
			
		GravityField* GetObjectAtPoint(const csl::math::Vector3& in_rPoint) const
		{
			rpAabbTree->Verify();
			return findGravityField(in_rPoint, 0.1f, nullptr);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}
