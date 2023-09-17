#pragma once

namespace app::xgame
{
	class MsgGetAnimal : public fnd::Message
	{
	public:
		size_t AnimalCount;
		
		inline const static unsigned int MessageID = 0x609B;

		MsgGetAnimal(size_t in_animalCount) : Message(MessageID), AnimalCount(in_animalCount)
		{

		}

		Message* Clone() override
		{
			return new MsgGetAnimal(*this);
		}
	};
}