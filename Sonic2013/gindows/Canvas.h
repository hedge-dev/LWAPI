#pragma once

namespace gindows
{
	using namespace device;
	
	class Canvas : Object
	{
	protected:
		Font* m_pFont{};
		Graphics* m_pGraphics{};
		csl::ut::Point2<int> m_P1{ 0, 0 };
		csl::ut::Rectangle2<int> m_R1{ 0, 0, 0, 0 };
		csl::ut::Color8* m_pBackColor{};
		csl::ut::Color8* m_pForeColor{};
		void* m_Unk1{};
		void* m_Unk2{};
		void* m_Unk3{};
		csl::ut::Point2<int> m_P2{ 0, 0 };
		void* m_Unk4{};
		csl::ut::Rectangle2<int> m_Rectangles[10]{};
		
	public:
		Canvas();
	};
}


#include "Manager.h"
inline gindows::Canvas::Canvas()
{
	auto* manager = Manager::GetInstance();
	
	m_pFont = manager->GetDefaultFontPointer();
	m_pGraphics = manager->GetGraphicsPointer();
	m_pBackColor = manager->GetDefaultBackColorPointer();
	m_pForeColor = manager->GetDefaultForeColorPointer();
}