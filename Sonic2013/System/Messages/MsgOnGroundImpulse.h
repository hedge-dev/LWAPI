#pragma once

namespace app::xgame
{
	class MsgOnGroundImpulse : public fnd::Message
	{
	public:
		typedef int EPanelType;

		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};
		float Unk3{};
		csl::math::Vector3 UpDirection{ 0.0f, 1.0f, 0.0f };
		EPanelType PanelType{};
		bool Unk6{};
		bool Unk7{};

		inline const static unsigned int MessageID = 0x6001;

		MsgOnGroundImpulse(const csl::math::Vector3& in_rUnk1, const csl::math::Vector3& in_rUnk2, float in_unk3, EPanelType in_panelType)
			: Message(MessageID)
			, Unk1(in_rUnk1)
			, Unk2(in_rUnk2)
			, Unk3(in_unk3)
			, PanelType(in_panelType)

		{
			
		}

		Message* Clone() override
		{
			return new MsgOnGroundImpulse(*this);
		}
	};
}