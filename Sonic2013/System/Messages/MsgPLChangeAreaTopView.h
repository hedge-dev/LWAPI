#pragma once

namespace app::xgame
{
	class MsgPLChangeAreaTopView : public fnd::Message
	{
	public:
		bool IsTopView{};

		inline const static unsigned int MessageID = 0x509B;

		MsgPLChangeAreaTopView() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLChangeAreaTopView(*this);
		}
	};
}