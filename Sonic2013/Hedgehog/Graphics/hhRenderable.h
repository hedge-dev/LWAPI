#pragma once

namespace app::gfx
{
	class RenderableContainer;
	class Renderable : public hh::base::CRefCountObject
	{
	public:
		typedef int EViewMask;

		RenderableContainer* m_pContainer{};
		csl::ut::LinkListNode m_ListNode{};
		char m_OpaPriority{ static_cast<char>(0x80) };
		char m_XluPriority{ static_cast<char>(0x80) };
		char m_Option{ 1 };
		char m_Unk1{ 1 };
		char m_Scene{ 1 };
		char m_SubScene{ -1 };
		csl::ut::FixedString<32> m_Name{};
		RenderableEvent m_OpaEvent{ this };
		RenderableEvent m_XluEvent{ this };
		uint m_CameraTargets{ 1 };
		char m_Unk3{ static_cast<char>(0x80) };

		~Renderable() override;
		Renderable()
		{
			m_XluEvent.m_Unk1 = 0;
		}

		void SetName(const char* in_pName)
		{
			m_Name = in_pName;
		}

		virtual void* GetMTSync() { return nullptr; }
		virtual void Render(const hh::gfx::RenderEventParam& in_param) = 0;
		virtual void CalcView() { }
		virtual void UpdateFrame() { }
		virtual bool CheckEnable() { return true; }
	};
}