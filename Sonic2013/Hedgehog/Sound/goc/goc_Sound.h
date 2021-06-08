#pragma once

namespace app::game
{
	enum ESoundTransType {};
	struct SoundFollowHandleInfo
	{
		csl::math::Vector3 m_Position{};
		csl::ut::Enum<ESoundTransType, char> m_TransType{};
		csl::ut::Bitset<char> m_Flags{};
		size_t m_Unk1{};
		fnd::SoundHandle m_Handle{};
	};
	
	class GOCSound : public fnd::GOComponent
	{
	public:
		struct Description
		{
			size_t m_SoundCount{};
			size_t m_3DSoundCount{};
		};
		
	protected:
		inline static const fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<const fnd::GOComponentClass*>(ASLR(0x00FD7908));

		fnd::SoundPlayer* m_pSoundPlayer{};
		fnd::HFrame* m_pTransform{};
		csl::ut::ObjectMoveArray<fnd::SoundHandle> m_PlayHandles{ GetAllocator() };
		csl::ut::ObjectMoveArray<SoundFollowHandleInfo> m_FollowInfo{ GetAllocator() };

		
	public:
		GOCSound() = delete;
		
		void Setup(const Description& rDesc)
		{
			m_PlayHandles.change_allocator(GetAllocator());
			m_FollowInfo.change_allocator(GetAllocator());

			if (rDesc.m_SoundCount)
				m_PlayHandles.reserve(rDesc.m_SoundCount);

			if (rDesc.m_3DSoundCount)
				m_FollowInfo.reserve(rDesc.m_3DSoundCount);
			
			m_Flags.set(2, rDesc.m_SoundCount || rDesc.m_3DSoundCount);
		}

		inline static void SimpleSetup(GameObject* pObject, size_t soundCount, size_t soundCount3d)
		{
			if (!pObject)
				return;
			
			auto* pSound = pObject->GetComponent<GOCSound>();
			if (!pSound)
				return;

			pSound->Setup(Description{ soundCount, soundCount3d });
		}

	protected:
		void OnCreateSoundHandle(fnd::SoundHandle& rHandle)
		{
			if (rHandle && rHandle.IsLoop())
				m_PlayHandles.push_back(rHandle);
		}
		
	public:
		fnd::SoundHandle CreateSoundHandle(const char* pName, float tween, fnd::SoundDeviceTag device)
		{
			fnd::SoundParam param{};
			param.m_TweenFactor = tween;
			param.m_Device = device;
			
			fnd::SoundHandle handle = m_pSoundPlayer->Play(2, pName, param);
			OnCreateSoundHandle(handle);

			return handle;
		}

		fnd::SoundHandle CreateSoundHandle3D(const char* pName, const csl::math::Vector3& rPos, float tween, fnd::SoundDeviceTag device)
		{
			fnd::SoundParam param{};
			param.m_TweenFactor = tween;
			param.m_Device = device;

			fnd::SoundHandle handle = m_pSoundPlayer->Play3D(2, pName, rPos, param);
			OnCreateSoundHandle(handle);

			return handle;
		}
		
		fnd::SoundHandle Play(const char* pName, float tween)
		{
			return CreateSoundHandle(pName, tween, { HH_SOUND_DEVICE_AUTO });
		}

		fnd::SoundHandle PlayVoice(const char* pName)
		{
			return CreateSoundHandle(pName, 0, { HH_SOUND_DEVICE_AUTO });
		}
		
		fnd::SoundHandle Play3D(const char* pName, const csl::math::Vector3& rPos, float tween)
		{
			return CreateSoundHandle3D(pName, rPos, tween, { HH_SOUND_DEVICE_AUTO });
		}
		
		static const fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
	};
}