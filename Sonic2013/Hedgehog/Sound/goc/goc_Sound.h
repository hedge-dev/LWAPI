#pragma once

namespace app::game
{
	enum ESoundTransType {};
	struct SoundFollowHandleInfo
	{
		csl::math::Vector3 Position{};
		csl::ut::Enum<ESoundTransType, char> TransType{};
		csl::ut::Bitset<char> Flags{};
		fnd::HFrame* pTransform{};
		INSERT_PADDING(8);
		fnd::SoundHandle Handle{};
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
	private:
		inline static const fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<const fnd::GOComponentClass*>(ASLR(0x00FD7908));

	public:
		struct Description
		{
			size_t SoundCount{};
			size_t Sound3DCount{};
		};

		fnd::SoundPlayer* pSoundPlayer{};
		fnd::HFrame* pTransform{};
		csl::ut::ObjectMoveArray<fnd::SoundHandle> PlayHandles{ GetAllocator() };
		csl::ut::ObjectMoveArray<SoundFollowHandleInfo> FollowInfo{ GetAllocator() };
		
	public:
		GOCSound() = delete;
		
		void Setup(const Description& in_rDesc)
		{
			PlayHandles.change_allocator(GetAllocator());
			FollowInfo.change_allocator(GetAllocator());

			if (in_rDesc.SoundCount)
				PlayHandles.reserve(in_rDesc.SoundCount);

			if (in_rDesc.Sound3DCount)
				FollowInfo.reserve(in_rDesc.Sound3DCount);
			
			Flags.set(2, in_rDesc.SoundCount || in_rDesc.Sound3DCount);
		}

		inline static void SimpleSetup(GameObject* in_pObject, size_t in_soundCount, size_t in_soundCount3d)
		{
			if (!in_pObject)
				return;
			
			auto* pSound = in_pObject->GetComponent<GOCSound>();
			if (!pSound)
				return;

			pSound->Setup(Description{ in_soundCount, in_soundCount3d });
		}

	protected:
		void OnCreateSoundHandle(fnd::SoundHandle& in_rHandle)
		{
			if (in_rHandle && in_rHandle.IsLoop())
				PlayHandles.push_back(in_rHandle);
		}
		
	public:
		fnd::SoundHandle CreateSoundHandle(const char* in_pName, float in_tween, fnd::SoundDeviceTag in_device)
		{
			fnd::SoundParam param{};
			param.TweenFactor = in_tween;
			param.Device = in_device;
			
			fnd::SoundHandle handle = pSoundPlayer->Play(2, in_pName, param);
			OnCreateSoundHandle(handle);

			return handle;
		}

		fnd::SoundHandle CreateSoundHandle3D(const char* in_pName, const csl::math::Vector3& in_rPosition, float in_tween, fnd::SoundDeviceTag in_device)
		{
			fnd::SoundParam param{};
			param.TweenFactor = in_tween;
			param.Device = in_device;

			fnd::SoundHandle handle = pSoundPlayer->Play3D(2, in_pName, in_rPosition, param);
			OnCreateSoundHandle(handle);

			return handle;
		}

		fnd::SoundHandle Play(const char* in_pName, float in_tween)
		{
			return CreateSoundHandle(in_pName, in_tween, { HH_SOUND_DEVICE_AUTO });
		}

		fnd::SoundHandle Play(SoundPlayInfo& in_rPlayInfo)
		{
			return CreateSoundHandle(in_rPlayInfo.pCueName, in_rPlayInfo.Tween, in_rPlayInfo.Device);
		}

		fnd::SoundHandle PlayVoice(const char* in_pName)
		{
			return CreateSoundHandle(in_pName, 0, { HH_SOUND_DEVICE_AUTO });
		}
		
		fnd::SoundHandle Play3D(const char* in_pName, const csl::math::Vector3& in_rPosition, float in_tween)
		{
			return CreateSoundHandle3D(in_pName, in_rPosition, in_tween, { HH_SOUND_DEVICE_AUTO });
		}

		fnd::SoundHandle Play3D(const char* in_pName, float in_tween)
		{
			return CreateSoundHandle3D(in_pName, pTransform->Transform.GetTranslation(), in_tween, { HH_SOUND_DEVICE_AUTO });
		}

		fnd::SoundHandle Play3D(const SoundFollowFrameInfo& in_rFollowInfo)
		{
			SoundFollowHandleInfo handleInfo{};
			handleInfo.Flags = in_rFollowInfo.Flags;
			if (handleInfo.Flags.test(1))
				handleInfo.Position = in_rFollowInfo.Position;
		
			handleInfo.TransType = in_rFollowInfo.TransType;

			handleInfo.pTransform = in_rFollowInfo.pTransform;
			if (!handleInfo.pTransform)
				handleInfo.pTransform = pTransform;

			auto position = handleInfo.pTransform->Unk3.GetTranslation();
			if (handleInfo.Flags.test(1))
				position += handleInfo.Position;
		
			fnd::SoundHandle handle = CreateSoundHandle3D(in_rFollowInfo.pCueName, position, in_rFollowInfo.Tween, { HH_SOUND_DEVICE_AUTO });
			handleInfo.Handle = handle;

			if (FollowInfo.size() < FollowInfo.capacity())
			{
				FollowInfo.push_back_unchecked(handleInfo);
				return handle;
			}

			FollowInfo.push_back(handleInfo);
			return handle;
		}
		
		static const fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
	};
}