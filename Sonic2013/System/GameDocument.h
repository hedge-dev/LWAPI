#pragma once

namespace app
{
	namespace fnd 
	{
		class GameServiceClass;
		class GameService;
	}

	class GameObject;
	
	class GameDocument : public fnd::ReferencedObject
	{
	public:
		inline static GameDocument** ms_ppGameDocument = reinterpret_cast<GameDocument**>(ASLR(0xFEFEF4));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddGameObject, ASLR(0x0090B3C0), GameDocument* This, GameObject* object);
		inline static FUNCTION_PTR(fnd::GameService*, __thiscall, ms_fpGetServiceByClass, ASLR(0x0090B3C0), const GameDocument* This, fnd::GameServiceClass* cls);

	private:
		void* gameMode{};
		unsigned int unk1{};
		void* unk2{};
		float time{};

	public:
		void AddGameObject(GameObject* object)
		{
			ms_fpAddGameObject(this, object);
		}

		fnd::GameService* GetServiceByClass(fnd::GameServiceClass* cls) const
		{
			return ms_fpGetServiceByClass(this, cls);
		}

		template <typename T>
		T* GetService() const
		{
			return reinterpret_cast<T*>(GetServiceByClass(T::staticClass()));
		}

		inline static GameDocument* GetSingleton() 
		{
			return *ms_ppGameDocument;
		}
	};
}
