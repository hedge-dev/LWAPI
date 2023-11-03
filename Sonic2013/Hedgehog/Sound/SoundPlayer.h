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
		virtual SoundHandle Play(uint in_cue, const char* in_pName, const SoundParam& in_rParam) { return SoundHandle(nullptr); }
		virtual SoundHandle Play3D(uint in_cue, const char* in_pName, const csl::math::Vector3& in_rPos, const SoundParam& in_rParam) { return SoundHandle(nullptr); }
		virtual void SetListenerIdMap(const ListenerIdMapArgs& in_rArgs) {}
		virtual void SetSourceDafaultDistance(float, float) {}
		virtual void SetMasterVolume(uint in_id, float in_vol) {}
		virtual float GetMasterVolume(uint in_id) const { return 0; }
		virtual void SetMasterMute(uint in_id, bool in_mute) {}
		virtual bool IsMasterMute(uint in_id) const { return false; }
		virtual bool GetCueInfoList(const char* in_pName, csl::ut::MoveArray<ResSoundCueInfoDataTag>& in_rResults) const { return false; }
		virtual void DbgGet(csl::ut::MoveArray<dbg::SoundInfo::DataTag>& in_rResults) const { return; }
		virtual void DbgGetInfo(dbg::SoundInfoEx::DataTag& in_rResult) const { return; }
		virtual void Stop(const SoundHandle& in_rHandle, float in_fade) { return; }
		virtual void StopImm(const SoundHandle& in_rHandle) { return; }
		virtual void Pause(const SoundHandle& in_rHandle, bool in_imm, float in_fade) { return; }
		virtual void SetVolume(const SoundHandle& in_rHandle, float in_volume) { return; }
		virtual void SetBlockIdx(const SoundHandle& in_rHandle, int in_idx) { return; }
		virtual size_t GetNumBlocks(const SoundHandle& in_rHandle) const { return 0; }
		virtual size_t GetStatus(const SoundHandle& in_rHandle) const { return 0; }
		virtual bool IsPause(const SoundHandle& in_rHandle) const { return false; }
		virtual bool IsPlay(const SoundHandle& in_rHandle) const { return false; }
		virtual bool IsLoop(const SoundHandle& in_rHandle) const { return false; }
		virtual void SetSourcePosition(const SoundHandle& in_rHandle, const csl::math::Vector3& in_rPos) { return; }
		virtual void SetSourceVelocity(const SoundHandle& in_rHandle, const csl::math::Vector3& in_rVel) { return; }
		virtual float GetListernerDistance(const SoundHandle& in_rHandle, const SoundListenerHandle& in_rListener) { return 0; }
		virtual bool IsAisac(const SoundHandle& in_rHandle) const { return false; }
		virtual void SetAisac(const SoundHandle& in_rHandle, const char* in_pName, float in_value) { return; }
		virtual void AttachAisac(const SoundHandle& in_rHandle, const char* in_pName, float) { return; }
		virtual void DetachAisac(const SoundHandle& in_rHandle, const char* in_pName) { return; }
		virtual void DetachAisacAll(const SoundHandle& in_rHandle) { return; }
		virtual void ResetListener(const SoundListenerHandle& in_rHandle) { return; }
		virtual size_t GetListenerBufferId(const SoundListenerHandle& in_rHandle) const { return 0; }
		virtual size_t GetListenerId(const SoundListenerHandle& in_rHandle) const { return 0; }
		virtual void SetListenerPosition(const SoundListenerHandle& in_rHandle, const csl::math::Vector3& in_rPos) { return; }
		virtual void SetListenerVelocity(const SoundListenerHandle& in_rHandle, const csl::math::Vector3& in_rVel) { return; }
		virtual void SetListenerOrientation(const SoundListenerHandle& in_rHandle, const csl::math::Vector3&, const csl::math::Vector3&) { return; }
		virtual void SetListenerDistanceFactor(const SoundListenerHandle& in_rHandle, float) { return; }
		virtual void SetListenerFocusPoint(const SoundListenerHandle& in_rHandle, const csl::math::Vector3& in_rPoint) { return; }
		virtual void SetListenerDistanceFocusLevel(const SoundListenerHandle& in_rHandle, float in_level) { return; }
		virtual void SetListenerDirectionFocusLevel(const SoundListenerHandle& in_rHandle, float in_level) { return; }
		virtual void SystemPause(SoundHandleObj* in_pObj, bool, bool) { return; }
		virtual void CategoryPause(SoundHandleObj* in_pObj, bool, float) { return; }
		virtual void SetSendDevice(SoundHandleObj* in_pObj) { return; }
		virtual bool IsAisacGlobal(const char* in_pName) const { return false; }
		virtual size_t GetCategory(void*) const { return 0; }
	};
}

DEFINE_SINGLETONPTR(app::fnd::SoundPlayer, ASLR(0x00FD3CB8));