#pragma once

namespace app::Gimmick
{
	class CRingManager : fnd::GameService
	{
	protected:
		csl::ut::ObjectMoveArray<GameObjectHandle<GameObject>> m_Objects{ GetAllocator() };
		int m_Unk1{};
		float m_Unk2{};

	private:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FECC20));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00665470), void* pThis, const fnd::SUpdateInfo& rUpdateInfo);

	public:
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		void Update(const fnd::SUpdateInfo& rUpdateInfo) override
		{
			ms_fpUpdate(this, rUpdateInfo);
		}

		void RegisterRotateRing(GameObject* pObject)
		{
			GameObjectHandle handle(pObject);
			m_Objects.push_back(handle);
		}
	};
}