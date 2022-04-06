#pragma once

namespace app::fnd
{
	class SoundSystem : public ReferencedObject, public csl::fnd::SingletonPointer<SoundSystem>
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00FD4324));

		csl::ut::FixedString<64> m_Root{};
		FileBinder* m_pBinder{};

		virtual DEFINE_RTTI_GETTER;
		virtual void Update(float in_delta) {}
		virtual void RegisterData(void* in_pData, size_t in_size) {}
		virtual void UnregisterData() {}
		virtual void RegisterCueData(const char* in_pName, void* in_pData, size_t in_size, const char* in_a4);
		virtual void UnregisterCueData(const char* in_pName);
	};
}

DEFINE_SINGLETONPTR(app::fnd::SoundSystem, ASLR(0x00FD4328));