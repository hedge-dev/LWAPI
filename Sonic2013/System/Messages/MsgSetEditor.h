#pragma once

namespace app::SetEd
{
	class MsgUpdateSetEditor : public fnd::Message
	{
	public:
		inline static uint MessageID = 0x2007;

		MsgUpdateSetEditor() : fnd::Message(MessageID)
		{
			
		}
	};

	class MsgSetObjectEdited : public fnd::Message
	{
	public:
		inline static uint MessageID = 0x2008;

		MsgSetObjectEdited() : fnd::Message(MessageID)
		{

		}
	};

	class MsgPositionUpdatedFromSetEditor : public fnd::Message
	{
	public:
		inline static uint MessageID = 0x200D;

		MsgPositionUpdatedFromSetEditor() : fnd::Message(MessageID)
		{

		}
	};

	class MsgNotifyOnStartSetEditor : public fnd::Message
	{
	public:
		inline static uint MessageID = 0x200E;

		MsgNotifyOnStartSetEditor() : fnd::Message(MessageID)
		{

		}
	};
}