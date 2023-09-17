#pragma once

namespace app::Player
{
	class CStatePlugin : public PluginBase<CStateGOC>
	{
	public:
		CStatePlugin(const char* in_pName) : PluginBase<CStateGOC>(in_pName)
		{

		}
	};
}