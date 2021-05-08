#pragma once

inline void gindows::Control::SetFocus()
{
	Manager::GetInstance()->SetFocusControl(this);
}