#pragma once

namespace app::fnd
{
	class SoundHandleObj : public RefByHandleObject
	{
		void* m_pTag{};
		INSERT_PADDING(8) {};
		
	public:
		SoundHandleObj()
		{
			sizeof(SoundHandleObj);
		}
	};
}