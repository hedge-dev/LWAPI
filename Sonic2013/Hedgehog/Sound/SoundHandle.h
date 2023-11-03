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

		SoundHandle(SoundHandleObj* in_pObj) : Handle<SoundHandleObj>(in_pObj)
		{
			m_pPlayer = csl::fnd::Singleton<SoundPlayer>::GetInstance();
		}

		void StopImm();
		void Stop(float in_fade);
		void Pause(bool in_imm, float in_fade);
		void SetVolume(float in_vol);
		void SetBlockIdx(int in_idx);
		
		void SetPosition(const csl::math::Vector3& in_rPosition);
		void SetVelocity(const csl::math::Vector3& in_rVelocity);

		void SetAisac(const char* in_pName, float in_value);
		void AttachAisac(const char* in_pName);
		void DetachAisac(const char* in_me);
		void DetachAisacAll();
		
		bool IsPlay() const;
		bool IsLoop() const;
		bool IsPause() const;
		bool IsAisac() const;
		size_t GetStatus() const;
		size_t GetNumBlocks() const;
		float GetDistance(const SoundListenerHandle& in_rListener) const;
	};
}