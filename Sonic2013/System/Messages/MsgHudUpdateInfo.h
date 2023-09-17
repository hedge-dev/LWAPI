#pragma once

namespace app::xgame
{
	class MsgHudUpdateInfo : public fnd::Message
	{
	public:
		struct SInfo
		{
			INSERT_PADDING(36);
			int NumHearts{};
			INSERT_PADDING(4);
			int MaxNumHearts{};
			INSERT_PADDING(8);
		};

		SInfo Info{};

		inline const static unsigned int MessageID = 0xC000;
		
		MsgHudUpdateInfo(const SInfo& in_rInfo) : Message(MessageID), Info(in_rInfo)
		{

		}

		Message* Clone() override
		{
			return new MsgHudUpdateInfo(*this);
		}
	};
}