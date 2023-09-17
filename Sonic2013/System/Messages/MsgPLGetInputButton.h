#pragma once

namespace app::xgame
{
	class MsgPLGetInputButton : public fnd::Message
	{
	public:
		enum class Input : uint
		{
			Input0,
			UP,
			DOWN
		};

		enum class Status : uint
		{
			Status0,
			PRESSED
		};
		
		Input Key{};
		Status KeyStatus{};
		bool IsPressed{};
		
		inline const static unsigned int MessageID = 0x5027;
		
		MsgPLGetInputButton() : Message(MessageID)
		{

		}

		MsgPLGetInputButton(Input in_key, Status in_status) : Message(MessageID)
		{
			Key = in_key;
			KeyStatus = in_status;
		}

		Message* Clone() override
		{
			return new MsgPLGetInputButton(*this);
		}
	};
}