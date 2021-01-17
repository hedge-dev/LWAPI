#pragma once

namespace gindows
{
	class Manager : Object, csl::ut::NonCopyable
	{
	private:
		inline static Manager** ms_ppInstance = reinterpret_cast<Manager**>(ASLR(0x00FF00A4));
		inline static FUNCTION_PTR(void, __cdecl, ms_fpInitialize, ASLR(0x0096EE00));
		
	protected:
		ManagerImpl* m_pImpl{};
		WindowManager* m_pWindowManager{};

	public:
		static void Initialize()
		{
			ms_fpInitialize();
		}
		
		static Manager* GetInstance()
		{
			return *ms_ppInstance;
		}
		
		[[nodiscard]] device::Font* GetDefaultFontPointer() const
		{
			return m_pImpl->GetDefaultFontPointer();
		}

		[[nodiscard]] device::Graphics* GetGraphicsPointer() const
		{
			return m_pImpl->GetGraphicsPointer();
		}

		[[nodiscard]] device::DeviceMouse* GetMousePointer() const
		{
			return m_pImpl->GetMousePointer();
		}
		
		[[nodiscard]] const csl::ut::Color8* GetDefaultBackColorPointer() const
		{
			return m_pImpl->GetDefaultBackColorPointer();
		}

		[[nodiscard]] const csl::ut::Color8* GetDefaultForeColorPointer() const
		{
			return m_pImpl->GetDefaultBackColorPointer();
		}

		[[nodiscard]] const csl::ut::Color8* GetSelectCaptionColorL() const
		{
			return m_pImpl->GetSelectCaptionColorL();
		}

		[[nodiscard]] const csl::ut::Color8* GetSelectCaptionColorR() const
		{
			return m_pImpl->GetSelectCaptionColorR();
		}

		[[nodiscard]] const csl::ut::Color8* GetUnselectCaptionColor() const
		{
			return m_pImpl->GetUnselectCaptionColor();
		}
		
		void SetFont(uint id, device::Font* pFont) const
		{
			m_pImpl->SetFont(id, pFont);
		}

		void SetGraphics(device::Graphics* pGraphics) const
		{
			m_pImpl->SetGraphics(pGraphics);
		}

		void SetMouse(device::DeviceMouse* pMouse) const
		{
			m_pImpl->SetMouse(pMouse);
		}
		
		void SetDefaultFontIndex(size_t idx) const
		{
			m_pImpl->SetDefaultFontIndex(idx);
		}
	};
}