#include "hhSoundListenerHandle.h"
#pragma once

namespace app::fnd
{
	size_t SoundListenerHandle::GetIdx() const
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
	
	inline void SoundListenerHandle::SetPosition(const csl::math::Vector3& rPos)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerPosition(*this, rPos);
	}
	
	inline void SoundListenerHandle::SetVelocity(const csl::math::Vector3& rVel)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerVelocity(*this, rVel);
	}
	
	inline void SoundListenerHandle::SetFocusPoint(csl::math::Vector3& rPoint)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerFocusPoint(*this, rPoint);
	}
	
	inline void SoundListenerHandle::SetDirectionFocusLevel(float level)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerDirectionFocusLevel(*this, level);
	}
	
	inline void SoundListenerHandle::SetDistanceFocusLevel(float level)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerDistanceFocusLevel(*this, level);
	}
	
	inline void SoundListenerHandle::SetDistanceFactor(float factor)
	{
		if (m_pPlayer)
			m_pPlayer->SetListenerDistanceFactor(*this, factor);
	}
}