#pragma once

namespace app::fnd
{
	class SoundPlayer;
	
	class SoundListenerHandle : public Handle<SoundHandleObj>
	{
	protected:
		SoundPlayer* m_pPlayer{};

	public:
		SoundListenerHandle() : Handle<app::fnd::SoundHandleObj>(nullptr)
		{

		}

		SoundListenerHandle(SoundHandleObj* pObj) : Handle<SoundHandleObj>(pObj)
		{
			m_pPlayer = csl::fnd::Singleton<SoundPlayer>::GetInstance();
		}

		size_t GetIdx() const;
		size_t GetListenerId() const;
		void SetPosition(const csl::math::Vector3& rPos);
		void SetVelocity(const csl::math::Vector3& rVel);
		void SetFocusPoint(csl::math::Vector3& rPoint);
		void SetDirectionFocusLevel(float level);
		void SetDistanceFocusLevel(float level);
		void SetDistanceFactor(float factor);
	};
}