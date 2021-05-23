#pragma once

namespace app::dbg
{
	class FormObject : public gindows::Form
	{
	public:
		FormObject(const char* pName) : Form()
		{
			SetName(pName);
			m_OnExecute += csl::ut::MakePair(this, &FormObject::Update);
			m_OnRender += csl::ut::MakePair(this, &FormObject::Draw);
		}

		virtual void Update(gindows::Object* pSender, gindows::ExecuteEventArgs& args)
		{
			
		}

		virtual void Draw(gindows::Object* pSender, gindows::RenderEventArgs& args)
		{

		}
	};
}