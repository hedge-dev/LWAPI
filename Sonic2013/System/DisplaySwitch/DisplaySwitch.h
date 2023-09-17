#pragma once

namespace app
{
	class DisplaySwitchListener;

	class DisplaySwitch : public fnd::ReferencedObject, csl::fnd::SingletonPointer<DisplaySwitch>
	{
		enum State : int;
		
	public:
		csl::ut::Enum<State, char> m_State;
		INSERT_PADDING(16); // csl::ut::InplaceMoveArray<DisplaySwitchListener, 5>
		INSERT_PADDING(20) {};
		DisplayText m_DisplayText{};

		DisplaySwitch() {}
		~DisplaySwitch() override {} 
	};
}

DEFINE_SINGLETONPTR(app::DisplaySwitch, ASLR(0x00FD7358));