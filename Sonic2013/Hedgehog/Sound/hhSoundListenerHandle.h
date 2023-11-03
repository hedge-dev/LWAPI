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

		SoundListenerHandle(SoundHandleObj* in_pObj) : Handle<SoundHandleObj>(in_pObj)
		{
			m_pPlayer = csl::fnd::Singleton<SoundPlayer>::GetInstance();
		}

		size_t GetIdx() const;
		size_t GetListenerId() const;
		void SetPosition(const csl::math::Vector3& in_rPosition);
		void SetVelocity(const csl::math::Vector3& in_rVelocity);
		void SetFocusPoint(csl::math::Vector3& in_rPoint);
		void SetDirectionFocusLevel(float in_level);
		void SetDistanceFocusLevel(float in_level);
		void SetDistanceFactor(float in_factor);
	};
}