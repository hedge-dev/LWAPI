#pragma once
#pragma push_macro("DrawText")
#undef DrawText

namespace app::font
{
	class Font : public fnd::ReferencedObject
	{
	public:
		virtual bool IsInit() = 0;
		virtual void SetTextColor(uint in_color) = 0;
		virtual void SetTextSize(const csl::math::Vector2& in_rSize) = 0;
		virtual csl::math::Vector2 GetFontSize() = 0;
		virtual void Begin() {}
		virtual void End() {}
		virtual void DrawText(const csl::math::Vector2& in_rPos, const char* in_pText) = 0;
		virtual void DrawText(const csl::math::Vector2& in_rPos, const wchar_t* in_pText) = 0;
		virtual void DrawText(const csl::math::Vector2& in_rPos, char* in_pText) = 0;
		virtual void DrawText(const csl::math::Vector2& in_rPos, wchar_t* in_pText) = 0;
		virtual csl::math::Vector2 GetCharSize(wchar_t in_ch) = 0;
		virtual const wchar_t* ToWideString(const char* in_pText) = 0;
	};
}

#pragma pop_macro("DrawText")