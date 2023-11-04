#pragma once

namespace app::dbg
{
	class FormObject : public gindows::Form
	{
	public:
		FormObject(const char* in_pName) : Form()
		{
			SetName(in_pName);
			m_OnExecute += csl::ut::MakePair(this, &FormObject::Update);
			m_OnRender += csl::ut::MakePair(this, &FormObject::Draw);
		}

		virtual void Update(gindows::Object* in_pSender, gindows::ExecuteEventArgs& in_rArgs)
		{
			
		}

		virtual void Draw(gindows::Object* in_pSender, gindows::RenderEventArgs& in_rArgs)
		{

		}
	};
}