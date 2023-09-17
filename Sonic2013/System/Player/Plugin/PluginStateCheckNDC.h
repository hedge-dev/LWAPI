#pragma once

namespace app::Player
{
	class CPluginStateCheckNDC : public CStatePlugin
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E005B8);

	protected:

	public:
		CPluginStateCheckNDC() : CStatePlugin(ms_pName)
		{

		}
	};
}