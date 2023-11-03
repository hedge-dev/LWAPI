#pragma once

namespace app::gfx
{
	class RenderableContainer;
	
	class Renderable : public hh::base::CRefCountObject
	{
	public:
		typedef int EViewMask;

		RenderableContainer* pContainer{};
		csl::ut::LinkListNode ListNode{};
		char OpaPriority{ static_cast<char>(0x80) };
		char XluPriority{ static_cast<char>(0x80) };
		char Option{ 1 };
		char Unk1{ 1 };
		char Scene{ 1 };
		char SubScene{ -1 };
		csl::ut::FixedString<32> Name{};
		RenderableEvent OpaEvent{ this };
		RenderableEvent XluEvent{ this };
		uint CameraTargets{ 1 };
		char Unk3{ static_cast<char>(0x80) };

		~Renderable() override;
		Renderable()
		{
			XluEvent.Unk1 = 0;
		}

		void SetName(const char* in_pName)
		{
			Name = in_pName;
		}

		virtual void* GetMTSync() { return nullptr; }
		virtual void Render(const hh::gfx::RenderEventParam& in_rParam) = 0;
		virtual void CalcView() { }
		virtual void UpdateFrame() { }
		virtual bool CheckEnable() { return true; }
	};
}