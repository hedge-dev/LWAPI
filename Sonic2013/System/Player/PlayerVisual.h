#pragma once

namespace app::Player
{
	typedef int NodeID;

	inline static constexpr const char* ms_pNodeNames[] = { "SonicRoot", "Reference", "Hips", "Spine", "Spine1", "Neck", "Head",
		"Needle_B_C", "Needle1_B_C", "Needle_B_L", "Needle1_B_L", "Needle_B_R", "Needle1_B_R", "Needle_U_C", "Needle1_U_C", "Needle_U_L", "Needle1_U_L", "Needle_U_R", "Needle1_U_R",
		"Shoulder_L", "UpperArm_L", "ForeArm_L", "Elbow_L", "Hand_L",
		"Index1_L", "Index2_L", "Index3_L", "Middle1_L", "Middle2_L", "Middle3_L", "Pinky1_L", "Pinky2_L", "Pinky3_L", "Ring1_L", "Ring2_L", "Ring3_L", "Thumb1_L", "Thumb2_L", "Thumb3_L", "Wrist_L",
		"Shoulder_R", "UpperArm_R", "ForeArm_R", "Elbow_R", "Hand_R",
		"Index1_R", "Index2_R", "Index3_R", "Middle1_R", "Middle2_R", "Middle3_R", "Pinky1_R", "Pinky2_R", "Pinky3_R", "Ring1_R", "Ring2_R", "Ring3_R", "Thumb1_R", "Thumb2_R", "Thumb3_R", "Wrist_R",
		"Thigh_L", "Calf_L", "Foot_L", "Socks_L", "Toe_L", "Knee_L", "Thigh_R", "Calf_R", "Foot_R", "Socks_R", "Toe_R", "Knee_R", "Sonic_Body", "SonicEye_L", "SonicEye_R", "Sonic_Glove", "Sonic_Mouth" };

	inline const char* GetVisualHumanNodeName(NodeID in_nodeId)
	{
		return ms_pNodeNames[in_nodeId];
	}

	class CPlayerVisual : public fnd::ReferencedObject, public CVisualBase
	{
	public:
		const char* pVisualName{};
		csl::ut::Bitset<ushort> Unk1{};
		csl::ut::Bitset<ushort> Unk2{};
		EffectList* pEffects{}; // boost::intrusive_ptr<EffectList>
		ut::RefPtr<CVisualUnit> rpVisualUnit{};
		GOCReferenceHolder* pGocHolder{};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEffectList, ASLR(0x008F01F0), CPlayerVisual*, uint);

	public:
		CPlayerVisual(CPlayer* in_pPlayer, CVisualGOC* in_pVisualGoc, const char* in_pVisualName) : CVisualBase(in_pPlayer, in_pVisualGoc), pVisualName(in_pVisualName)
		{
			ASSERT_OFFSETOF(CPlayerVisual, rpVisualUnit, 40);
		}

		virtual void Update(float in_deltaTime) = 0;
		virtual void UpdateMatrix() { Update(0.0f); }
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		CVisualUnit* GetCurrentUnit()
		{
			if (!rpVisualUnit)
				return { nullptr };

			return rpVisualUnit.get();
		}

		CVisualUnit* GetCurrentUnit() const
		{
			if (!rpVisualUnit)
				return { nullptr };

			return rpVisualUnit.get();
		}

		void SetCurrentUnit(CVisualUnit* in_pVisualUnit)
		{
			rpVisualUnit = in_pVisualUnit;
		}

		void SetFlag(uint in_bit, bool in_enable)
		{
			Unk2.set(in_bit, in_enable);
		}

		void SetFlagSub(uint in_bit, bool in_enable)
		{
			Unk2.set(in_bit, in_enable);
		}

		void CreateEffectList(uint in_capacity)
		{
			ms_fpCreateEffectList(this, in_capacity);
		}

		void SetBlinkVisible(bool in_isVisible)
		{
			if (!pGocHolder)
				return;
		
			pGocHolder->SetBlinkVisible(in_isVisible);
		}
	};
}