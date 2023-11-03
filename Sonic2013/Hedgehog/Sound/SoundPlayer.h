#pragma once

namespace app::fnd
{
	class SoundPlayer : public ReferencedObject, csl::fnd::SingletonPointer<SoundPlayer>
	{
	public:
		struct ListenerIdMapArgs
		{
			
		};
		
		DEFINE_RTTI_PTR(ASLR(0x00FD431C));
		
		virtual const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const { return GetRuntimeTypeInfoStatic(); };
		virtual SoundHandle Play(uint cue, const char* pName, const SoundParam& rParam) { return SoundHandle(nullptr); }
		virtual SoundHandle Play3D(uint cue, const char* pName, const csl::math::Vector3& rPos, const SoundParam& rParam) { return SoundHandle(nullptr); }
		virtual void SetListenerIdMap(const ListenerIdMapArgs& args) {}
		virtual void SetSourceDafaultDistance(float, float) {}
		virtual void SetMasterVolume(uint id, float vol) {}
		virtual float GetMasterVolume(uint id) const { return 0; }
		virtual void SetMasterMute(uint id, bool mute) {}
		virtual bool IsMasterMute(uint id) const { return false; }
		virtual bool GetCueInfoList(const char* pName, csl::ut::MoveArray<ResSoundCueInfoDataTag>& rResults) const { return false; }
		virtual void DbgGet(csl::ut::MoveArray<dbg::SoundInfo::DataTag>& rResults) const { return; }
		virtual void DbgGetInfo(dbg::SoundInfoEx::DataTag& rResult) const { return; }
		virtual void Stop(const SoundHandle& rHandle, float fade) { return; }
		virtual void StopImm(const SoundHandle& rHandle) { return; }
		virtual void Pause(const SoundHandle& rHandle, bool imm, float fade) { return; }
		virtual void SetVolume(const SoundHandle& rHandle, float volume) { return; }
		virtual void SetBlockIdx(const SoundHandle& rHandle, int idx) { return; }
		virtual size_t GetNumBlocks(const SoundHandle& rHandle) const { return 0; }
		virtual size_t GetStatus(const SoundHandle& rHandle) const { return 0; }
		virtual bool IsPause(const SoundHandle& rHandle) const { return false; }
		virtual bool IsPlay(const SoundHandle& rHandle) const { return false; }
		virtual bool IsLoop(const SoundHandle& rHandle) const { return false; }
		virtual void SetSourcePosition(const SoundHandle& rHandle, const csl::math::Vector3& rPos) { return; }
		virtual void SetSourceVelocity(const SoundHandle& rHandle, const csl::math::Vector3& rVel) { return; }
		virtual float GetListernerDistance(const SoundHandle& rHandle, const SoundListenerHandle& rListener) { return 0; }
		virtual bool IsAisac(const SoundHandle& rHandle) const { return false; }
		virtual void SetAisac(const SoundHandle& rHandle, const char* pName, float value) { return; }
		virtual void AttachAisac(const SoundHandle& rHandle, const char* pName, float) { return; }
		virtual void DetachAisac(const SoundHandle& rHandle, const char* pName) { return; }
		virtual void DetachAisacAll(const SoundHandle& rHandle) { return; }
		virtual void ResetListener(const SoundListenerHandle& rHandle) { return; }
		virtual size_t GetListenerBufferId(const SoundListenerHandle& rHandle) const { return 0; }
		virtual size_t GetListenerId(const SoundListenerHandle& rHandle) const { return 0; }
		virtual void SetListenerPosition(const SoundListenerHandle& rHandle, const csl::math::Vector3& rPos) { return; }
		virtual void SetListenerVelocity(const SoundListenerHandle& rHandle, const csl::math::Vector3& rVel) { return; }
		virtual void SetListenerOrientation(const SoundListenerHandle& rHandle, const csl::math::Vector3&, const csl::math::Vector3&) { return; }
		virtual void SetListenerDistanceFactor(const SoundListenerHandle& rHandle, float) { return; }
		virtual void SetListenerFocusPoint(const SoundListenerHandle& rHandle, const csl::math::Vector3& rPoint) { return; }
		virtual void SetListenerDistanceFocusLevel(const SoundListenerHandle& rHandle, float level) { return; }
		virtual void SetListenerDirectionFocusLevel(const SoundListenerHandle& rHandle, float level) { return; }
		virtual void SystemPause(SoundHandleObj* pObj, bool, bool) { return; }
		virtual void CategoryPause(SoundHandleObj* pObj, bool, float) { return; }
		virtual void SetSendDevice(SoundHandleObj* pObj) { return; }
		virtual bool IsAisacGlobal(const char* pName) const { return false; }
		virtual size_t GetCategory(void*) const { return 0; }
	};
}

DEFINE_SINGLETONPTR(app::fnd::SoundPlayer, ASLR(0x00FD3CB8));