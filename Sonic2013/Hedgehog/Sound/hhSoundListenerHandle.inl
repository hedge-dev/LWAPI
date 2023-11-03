#include "hhSoundListenerHandle.h"
#pragma once

namespace app::fnd
{
	inline size_t SoundListenerHandle::GetIdx() const
	{
		if (m_pPlayer)
			return m_pPlayer->GetListenerBufferId(*this);
		
		return size_t();
	}
	
	inline size_t SoundListenerHandle::GetListenerId() const
	{
		if (m_pPlayer)
			return m_pPlayer->GetListenerId(*this);
		
		return size_t();
	}
	
	inline void SoundListenerHandle::SetPosition(const csl::math::Vector3& in_rPosition)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerPosition(*this, in_rPosition);
	}
	
	inline void SoundListenerHandle::SetVelocity(const csl::math::Vector3& in_rVelocity)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerVelocity(*this, in_rVelocity);
	}
	
	inline void SoundListenerHandle::SetFocusPoint(csl::math::Vector3& in_rPoint)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerFocusPoint(*this, in_rPoint);
	}
	
	inline void SoundListenerHandle::SetDirectionFocusLevel(float in_level)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerDirectionFocusLevel(*this, in_level);
	}
	
	inline void SoundListenerHandle::SetDistanceFocusLevel(float in_level)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerDistanceFocusLevel(*this, in_level);
	}
	
	inline void SoundListenerHandle::SetDistanceFactor(float in_factor)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerDistanceFactor(*this, in_factor);
	}
}