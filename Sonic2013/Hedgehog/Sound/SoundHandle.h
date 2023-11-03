#pragma once

namespace app::fnd
{
	class SoundPlayer;
	class SoundListenerHandle;
	
	class SoundHandle : public Handle<SoundHandleObj>
	{
	protected:
		SoundPlayer* m_pPlayer{};

	public:
		SoundHandle() : Handle<app::fnd::SoundHandleObj>(nullptr)
		{
			
		}

		SoundHandle(SoundHandleObj* pObj) : Handle<SoundHandleObj>(pObj)
		{
			m_pPlayer = csl::fnd::Singleton<SoundPlayer>::GetInstance();
		}

		void StopImm();
		void Stop(float fade);
		void Pause(bool imm, float fade);
		void SetVolume(float vol);
		void SetBlockIdx(int idx);
		
		void SetPosition(const csl::math::Vector3& rPos);
		void SetVelocity(const csl::math::Vector3& rVel);

		void SetAisac(const char* pName, float value);
		void AttachAisac(const char* pName);
		void DetachAisac(const char* pName);
		void DetachAisacAll();
		
		bool IsPlay() const;
		bool IsLoop() const;
		bool IsPause() const;
		bool IsAisac() const;
		size_t GetStatus() const;
		size_t GetNumBlocks() const;
		float GetDistance(const SoundListenerHandle& rListener) const;
	};
}