#include "hhSoundHandle.h"
#pragma once

namespace app::fnd
{
	inline void SoundHandle::Stop(float in_fade)
	{
		if (m_pPlayer)
			m_pPlayer->Stop(*this, in_fade);
	}
	
	inline void SoundHandle::StopImm()
	{
		if (m_pPlayer)
			m_pPlayer->StopImm(*this);
	}
	
	inline void SoundHandle::Pause(bool in_imm, float in_fade)
	{
		if (m_pPlayer)
			m_pPlayer->Pause(*this, in_imm, in_fade);
	}
	
	inline void SoundHandle::SetVolume(float in_vol)
	{
		if (m_pPlayer)
			m_pPlayer->SetVolume(*this, in_vol);
	}
	
	inline void SoundHandle::SetBlockIdx(int in_idx)
	{
		if (m_pPlayer)
			m_pPlayer->SetBlockIdx(*this, in_idx);
	}
	
	inline void SoundHandle::SetPosition(const csl::math::Vector3& in_rPosition)
	{
		if (m_pPlayer)
			m_pPlayer->SetSourcePosition(*this, in_rPosition);
	}
	
	inline void SoundHandle::SetVelocity(const csl::math::Vector3& in_rVelocity)
	{
		if (m_pPlayer)
			m_pPlayer->SetSourceVelocity(*this, in_rVelocity);
	}
	
	inline void SoundHandle::SetAisac(const char* in_pName, float in_value)
	{
		if (m_pPlayer)
			m_pPlayer->SetAisac(*this, in_pName, in_value);
	}
	
	inline void SoundHandle::AttachAisac(const char* in_pName)
	{
		if (m_pPlayer)
			m_pPlayer->AttachAisac(*this, in_pName, 0);
	}
	
	inline void SoundHandle::DetachAisac(const char* in_pName)
	{
		if (m_pPlayer)
			m_pPlayer->DetachAisac(*this, in_pName);
	}
	
	inline void SoundHandle::DetachAisacAll()
	{
		if (m_pPlayer)
			m_pPlayer->DetachAisacAll(*this);
	}
	
	inline bool SoundHandle::IsPlay() const
	{
		if (m_pPlayer)
			return m_pPlayer->IsPlay(*this);
		
		return false;
	}
	
	inline bool SoundHandle::IsLoop() const
	{
		if (m_pPlayer)
			return m_pPlayer->IsLoop(*this);
		
		return false;
	}
	
	inline bool SoundHandle::IsPause() const
	{
		if (m_pPlayer)
			return m_pPlayer->IsPause(*this);
		
		return false;
	}
	
	inline bool SoundHandle::IsAisac() const
	{
		if (m_pPlayer)
			return m_pPlayer->IsAisac(*this);
		
		return false;
	}
	
	inline size_t SoundHandle::GetStatus() const
	{
		if (m_pPlayer)
			return m_pPlayer->GetStatus(*this);
		
		return size_t();
	}
	
	inline size_t SoundHandle::GetNumBlocks() const
	{
		if (m_pPlayer)
			return m_pPlayer->GetNumBlocks(*this);
		
		return size_t();
	}
	
	inline float SoundHandle::GetDistance(const SoundListenerHandle& in_rListener) const
	{
		if (m_pPlayer)
			return m_pPlayer->GetListernerDistance(*this, in_rListener);
		
		return 0.0f;
	}
}