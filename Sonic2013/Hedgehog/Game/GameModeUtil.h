#pragma once

namespace app
{
	class GameModeUtil
	{
	public:
		template<typename T>
		class Event : public TiFsmBasicEvent<T>
		{
		public:
			Event(const TiFsmBasicEvent<T>& in_event) : TiFsmBasicEvent<T>(in_event)
			{
				
			}
		};
	};
}