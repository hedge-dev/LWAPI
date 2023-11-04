#pragma once

namespace app::Gimmick
{
	class CRingManager : fnd::GameService
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00665470), CRingManager*, const fnd::SUpdateInfo&);
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FECC20));

	protected:
		csl::ut::ObjectMoveArray<GameObjectHandle<GameObject>> m_Objects{ GetAllocator() };
		int m_Unk1{};

	public:
		float Unk2{};

	public:
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ms_fpUpdate(this, in_rUpdateInfo);
		}

		void RegisterRotateRing(GameObject* in_pObject)
		{
			GameObjectHandle handle(in_pObject);
			m_Objects.push_back(handle);
		}
	};
}