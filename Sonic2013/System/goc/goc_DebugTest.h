#pragma once

namespace app::debug
{
	class GOCDebugTest : public fnd::GOComponent
	{
		const char* GetFamilyID() override
		{
			return "GOCDebugTest";
		}

	public:
		GOCDebugTest() : GOComponent()
		{
			componentType = 7;
			componentFlags = 7;
			componentStats = 0x200;
		}
	};
}