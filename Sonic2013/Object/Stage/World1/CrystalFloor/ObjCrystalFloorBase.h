#pragma once

namespace app::ObjCrystalFloorBaseUtil
{
	inline void CreateUpDebris(const math::CalculatedTransform& in_rTransform, const csl::math::Vector3 in_rUnk1, const debris::ResRandomSpaceDebris& in_rDebris, GameDocument* in_pDocument)
	{
		debris::SRandomSpaceDebrisInfo debrisInfo{};
		debrisInfo.Transform.Position = { in_rTransform.GetTranslation() - (math::Vector3Rotate(in_rTransform.GetRotationQuaternion(), { csl::math::Vector3::UnitY() }) * 20.0f) };
		debrisInfo.Transform.SetFlag(1);
		debrisInfo.Transform.Rotation = in_rTransform.GetRotationQuaternion();
		debrisInfo.Transform.SetFlag(1);
		debrisInfo.Unk1 = 400.0f;
		debrisInfo.Unk2 = 2.0f;
		debrisInfo.Unk3 = 0.5f;
		debrisInfo.Unk4.set(0);
		debrisInfo.Unk5 = in_rUnk1;
		debrisInfo.Unk6 = math::Vector3Rotate(in_rTransform.GetRotationQuaternion(), { csl::math::Vector3::UnitY() });
		debrisInfo.Unk7 = 15.0f;
		debrisInfo.Unk8 = 1.0f;
		debrisInfo.Unk4.set(2);
		debrisInfo.Unk10 = 0.0f;
		debrisInfo.Unk11 = 20.0f;
		debrisInfo.Unk4.set(1);
		debrisInfo.field_80 = debrisInfo.Transform.Position;
		debrisInfo.Unk9 = 1.0f;
		debrisInfo.SetModelRes(in_rDebris, 24);
		debrisInfo.Unk14 = 3;
		debrisInfo.Unk15 = 30.0f * 0.5f;
		debrisInfo.Unk16 = 20.0f * 0.5f;
		debrisInfo.Unk17 = debrisInfo.Unk15;
		debrisUtil::CreateRandomSpaceDebris(*in_pDocument, debrisInfo);
	}

	inline void CreateDownDebris(const math::CalculatedTransform& in_rTransform, const csl::math::Vector3 in_rUnk1, const debris::ResRandomSpaceDebris& in_rDebris, GameDocument* in_pDocument)
	{
		debris::SRandomSpaceDebrisInfo debrisInfo{};
		debrisInfo.Transform.Position = in_rTransform.GetTranslation();
		debrisInfo.Transform.SetFlag(1);
		debrisInfo.Transform.Rotation = in_rTransform.GetRotationQuaternion();
		debrisInfo.Transform.SetFlag(1);
		debrisInfo.Unk1 = 60.0f;
		debrisInfo.Unk2 = 2.0f;
		debrisInfo.Unk3 = 0.5f;
		debrisInfo.Unk4.set(0);
		debrisInfo.Unk5 = in_rUnk1;
		debrisInfo.Unk6 = { -math::Vector3Rotate(in_rTransform.GetRotationQuaternion(), { csl::math::Vector3::UnitY() }) };
		debrisInfo.Unk7 = 5.0f;
		debrisInfo.Unk8 = 1.0f;
		debrisInfo.Unk4.set(2);
		debrisInfo.Unk10 = 0.0f;
		debrisInfo.Unk11 = 5.0f;
		debrisInfo.Unk4.set(1);
		debrisInfo.field_80 = debrisInfo.Transform.Position;
		debrisInfo.Unk9 = 1.0f;
		debrisInfo.SetModelRes(in_rDebris, 24);
		debrisInfo.Unk14 = 3;
		debrisInfo.Unk15 = 30.0f * 0.5f;
		debrisInfo.Unk16 = 20.0f * 0.5f;
		debrisInfo.Unk17 = debrisInfo.Unk15;
		debrisUtil::CreateRandomSpaceDebris(*in_pDocument, debrisInfo);
	}
}