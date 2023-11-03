#pragma once

namespace app::worldmap
{
	class touchcontroller
	{
	public:
		csl::ut::Bitset<uint> Unk1{};
		csl::math::Vector2 Unk2{};
		csl::math::Vector2 Unk3{};
		csl::math::Vector2 Unk4{};
		csl::math::Vector2 Unk5{};
		float Unk6{};
		float Unk7{};
		INSERT_PADDING(20);
		float TouchNonPermissiveTime{ 0.15f };
		float Unk9{};

		void SetTouchNonPermissiveTime(float in_time)
		{
			TouchNonPermissiveTime = in_time;
		}
	};
}

namespace app::game
{
	class TouchStatus
	{
		csl::ut::Bitset<ushort> Unk1{};
		float Unk2{};
		float Unk3{};
		float Unk4{};
		float Unk5{};
	};

	class GOCCharacterInput : public fnd::GOComponent 
	{
	private:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7588));

	public:
		int Unk1{ -1 };
		int Unk2{};
		csl::ut::Bitset<uint> Unk3{};
		csl::math::Vector2 StickInput{};
		csl::math::Vector2 SubStickInput{};
		float Unk6{};
		float Unk7{};
		float Unk8{};
		csl::math::Vector3 Unk9{};
		csl::ut::Bitset<ushort> Unk10[4];
		TouchStatus TouchStatus{};
		INSERT_PADDING(16) {};
		csl::math::Vector3 Unk11{};
		float Unk12{};
		float Unk13{};
		csl::math::Vector2 Unk14{};
		float Unk15{};
		float Unk16{};
		float Unk17{};
		float Unk18{};
		float Unk19{};
		float Unk20{};
		csl::math::Vector3 Unk21{};
		csl::math::Vector3 Unk22{};
		csl::math::Vector3 Unk23{};
		csl::math::Matrix34 Unk24{};
		csl::math::Matrix34 Unk25{};
		CWorld* pWorld{};
		int Unk26{};
		int Unk27{};
		ut::ScopedPtr<worldmap::touchcontroller> spTouchController{};
		float Unk28{};
		float Unk29{};
		csl::math::Vector2 TouchPanelSize{};
		float Unk31{};
		float Unk32{};
		float Unk33{};
		float Unk34{};
		float Unk35{};
		float Unk36{};

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		GOCCharacterInput()
		{
			spTouchController.reset(new(m_pAllocator) worldmap::touchcontroller());
		}

		Render::CameraParam* GetCameraParam() const
		{
			if (pWorld)
				return pWorld->GetCamera(Unk2);

			return { nullptr };
		}

		csl::math::Vector2 GetStick() const
		{
			return StickInput;
		}
		
		csl::math::Vector2 GetSubStick() const
		{
			return SubStickInput;
		}

		csl::math::Vector2 GetCorrectedStick() const
		{
			csl::math::Vector2 correctedStick;
			CorrectStickParameter(StickInput, &correctedStick);

			return correctedStick;
		}

		csl::math::Vector2 GetCorrectedSubStick() const
		{
			csl::math::Vector2 correctedSubStick;
			CorrectStickParameter(SubStickInput, &correctedSubStick);

			return correctedSubStick;
		}

		void CorrectStickParameter(const csl::math::Vector2& in_rStickVec, csl::math::Vector2* out_pCorrectedVec) const
		{
			csl::math::Vector2 normalizedInput{};
			float length{};
			if (!math::Vector2Normalize(in_rStickVec, &normalizedInput, &length))
			{
				*out_pCorrectedVec = in_rStickVec;
				return;
			}

			float input{};
			if (length * 1.25f <= 0.75f)
			{
				input = (length * 1.25f / 0.75f) * 0.6f;
				if (input < 0.1f)
				{
					input = 0.0f;
				}
				else
				{
					input = (length * 1.25f - 0.75f) * 4.0f * 0.4f + 0.6f;
				}
			}

			*out_pCorrectedVec = { normalizedInput * csl::math::Min(input, 1.0f) };
		}

		bool IsEnable() const
		{
			return Unk3.test(2);
		}

		void SetEnable(bool in_enable)
		{
			Unk3.set(2, in_enable);
		}

		bool IsEnableTouchPanel() const
		{
			return Unk3.test(7);
		}

		void SetEnableTouchPanel(bool in_enable)
		{
			if (in_enable && !Unk3.test(7))
			{
				TouchPanelSize.Set(640.0f, 360.0f);
			}

			Unk3.set(7);
		}

		void SetTouchNonPermissiveTime(float in_time)
		{
			spTouchController->SetTouchNonPermissiveTime(in_time);
		}

		bool IsValidPressJumpPrecade() const
		{
			return Unk3.test(3) && Unk29 > 0.0f;
		}

		void ResetAccAndGyroForDebug()
		{

		}
	};
}