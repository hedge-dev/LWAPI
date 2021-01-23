#pragma once
#pragma push_macro("DrawText")
#undef DrawText

namespace app::font
{
	class Font : public fnd::ReferencedObject
	{
	public:
		virtual bool IsInit() = 0;
		virtual void SetTextColor(uint color) = 0;
		virtual void SetTextSize(const csl::math::Vector2& size) = 0;
		virtual csl::math::Vector2* GetFontSize(csl::math::Vector2* pSize) = 0;
		virtual void Begin() {}
		virtual void End() {}
		virtual void DrawText(const csl::math::Vector2& pos, const char* text) = 0;
		virtual void DrawText(const csl::math::Vector2& pos, const wchar_t* text) = 0;
		virtual void DrawText(const csl::math::Vector2& pos, char* text) = 0;
		virtual void DrawText(const csl::math::Vector2& pos, wchar_t* text) = 0;
		virtual csl::math::Vector2* GetCharSize(wchar_t ch, csl::math::Vector2* pSize) = 0;
		virtual const wchar_t* ToWideString(const char* text) = 0;
	};
}

#pragma pop_macro("DrawText")