#include "hhSoundHandle.h"
#pragma once

namespace app::fnd
{
	inline void SoundHandle::Stop(float fade)
	{
		if (m_pPlayer)
			m_pPlayer->Stop(*this, fade);
	}
	
	inline void SoundHandle::StopImm()
	{
		if (m_pPlayer)
			m_pPlayer->StopImm(*this);
	}
	
	inline void SoundHandle::Pause(bool imm, float fade)
	{
		if (m_pPlayer)
			m_pPlayer->Pause(*this, imm, fade);
	}
	
	inline void SoundHandle::SetVolume(float vol)
	{
		if (m_pPlayer)
			m_pPlayer->SetVolume(*this, vol);
	}
	
	inline void SoundHandle::SetBlockIdx(int idx)
	{
		if (m_pPlayer)
			m_pPlayer->SetBlockIdx(*this, idx);
	}
	
	inline void SoundHandle::SetPosition(const csl::math::Vector3& rPos)
	{
		if (m_pPlayer)
			m_pPlayer->SetSourcePosition(*this, rPos);
	}
	
	inline void SoundHandle::SetVelocity(const csl::math::Vector3& rVel)
	{
		if (m_pPlayer)
			m_pPlayer->SetSourceVelocity(*this, rVel);
	}
	
	inline void SoundHandle::SetAisac(const char* pName, float value)
	{
		if (m_pPlayer)
			m_pPlayer->SetAisac(*this, pName, value);
	}
	
	inline void SoundHandle::AttachAisac(const char* pName)
	{
		if (m_pPlayer)
			m_pPlayer->AttachAisac(*this, pName, 0);
	}
	
	inline void SoundHandle::DetachAisac(const char* pName)
	{
		if (m_pPlayer)
			m_pPlayer->DetachAisac(*this, pName);
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
	
	inline float SoundHandle::GetDistance(const SoundListenerHandle& rListener) const
	{
		if (m_pPlayer)
			return m_pPlayer->GetListernerDistance(*this, rListener);
		
		return 0.0f;
	}
}