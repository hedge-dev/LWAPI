#pragma once

namespace app::game
{
	enum ESoundTransType {};
	struct SoundFollowHandleInfo
	{
		csl::math::Vector3 m_Position{};
		csl::ut::Enum<ESoundTransType, char> m_TransType{};
		csl::ut::Bitset<char> m_Flags{};
		fnd::HFrame* pTransform{};
		INSERT_PADDING(8);
		fnd::SoundHandle m_Handle{};
	};

	struct SoundFollowFrameInfo
	{
		const char* pCueName{};
		fnd::SoundDeviceTag Device{};
		float Tween{};
		INSERT_PADDING(20);
		csl::ut::Bitset<char> Flags{};
		int TransType{};
		INSERT_PADDING(8);
		fnd::HFrame* pTransform{};
		csl::math::Vector3 Position{};
	};

	struct SoundPlayInfo
	{
		const char* pCueName{};
		fnd::SoundDeviceTag Device{};
		float Tween{};
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

		fnd::SoundHandle Play(SoundPlayInfo& in_rPlayInfo)
		{
			return CreateSoundHandle(in_rPlayInfo.pCueName, in_rPlayInfo.Tween, in_rPlayInfo.Device);
		}

		fnd::SoundHandle PlayVoice(const char* pName)
		{
			return CreateSoundHandle(pName, 0, { HH_SOUND_DEVICE_AUTO });
		}
		
		fnd::SoundHandle Play3D(const char* pName, const csl::math::Vector3& rPos, float tween)
		{
			return CreateSoundHandle3D(pName, rPos, tween, { HH_SOUND_DEVICE_AUTO });
		}

		fnd::SoundHandle Play3D(const char* pName, float tween)
		{
			return CreateSoundHandle3D(pName, m_pTransform->m_Transform.GetTranslation(), tween, { HH_SOUND_DEVICE_AUTO });
		}

		fnd::SoundHandle Play3D(const SoundFollowFrameInfo& in_rFollowInfo)
		{
			SoundFollowHandleInfo handleInfo{};
			handleInfo.m_Flags = in_rFollowInfo.Flags;
			if (handleInfo.m_Flags.test(1))
				handleInfo.m_Position = in_rFollowInfo.Position;
		
			handleInfo.m_TransType = in_rFollowInfo.TransType;

			handleInfo.pTransform = in_rFollowInfo.pTransform;
			if (!handleInfo.pTransform)
				handleInfo.pTransform = m_pTransform;

			auto position = handleInfo.pTransform->m_Unk3.GetTranslation();
			if (handleInfo.m_Flags.test(1))
				position += handleInfo.m_Position;
		
			fnd::SoundHandle handle = CreateSoundHandle3D(in_rFollowInfo.pCueName, position, in_rFollowInfo.Tween, { HH_SOUND_DEVICE_AUTO });
			handleInfo.m_Handle = handle;

			if (m_FollowInfo.size() < m_FollowInfo.capacity())
			{
				m_FollowInfo.push_back_unchecked(handleInfo);
				return handle;
			}

			m_FollowInfo.push_back(handleInfo);
			return handle;
		}
		
		static const fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
	};
}