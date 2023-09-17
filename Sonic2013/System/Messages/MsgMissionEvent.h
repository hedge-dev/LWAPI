#pragma once

namespace app::xgame
{
	class MissionEventID
	{
	public:
		typedef int Type;
	};

	class MsgMissionEvent : public fnd::Message
	{
	public:
		MissionEventID::Type Type{};
		int Unk1{};

		inline const static unsigned int MessageID = 0x4008;

		MsgMissionEvent() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgMissionEvent(*this);
		}
	};
}