#pragma once

namespace app
{
	class CActivationManager;
	
	class alignas(16) CActivationVolume
	{
		friend CActivationManager;
	protected:
		CActivationManager* m_pManager{};
		size_t m_Flags{};
		
	public:
		INSERT_PADDING(8){};

	protected:
		csl::math::Sphere m_Volume;
		csl::ut::LinkListNode m_ListNode{ nullptr, nullptr };

	public:
		CActivationVolume()
		{
			
		}

		const csl::math::Sphere& GetVolume() const
		{
			return m_Volume;
		}

		void SetVolume(const csl::math::Sphere& vol)
		{
			m_Volume = vol;
		}
	};
}