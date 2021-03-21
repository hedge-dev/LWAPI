#pragma once
namespace app::animation
{
	class CharactorAnimation;
	
	class AnimationCallback : public fnd::ReferencedObject
	{
	public:
		virtual void Callback(CharactorAnimation* pAnimation, ETriggerValueType type, CallbackParam param) = 0;
	};

	template<class T>
	class AnimCallbackBridge : public AnimationCallback
	{
	public:
		typedef void (T::*MemFunc)(CharactorAnimation* pAnimation, ETriggerValueType type, CallbackParam param);
		
	protected:
		T* m_pObj{};
		MemFunc m_pFunc{};

	public:
		AnimCallbackBridge(T* pObj, MemFunc func) : m_pObj(pObj), m_pFunc(func)
		{
			
		}
		
		void Callback(CharactorAnimation* pAnimation, ETriggerValueType type, CallbackParam param) override
		{
			(m_pObj->*m_pFunc)(pAnimation, type, param);
		}
	};
	
	template<class T>
	AnimationCallback* CreateAnimCallback(T* pObj, typename AnimCallbackBridge<T>::MemFunc func, csl::fnd::IAllocator* pAlloc)
	{
		return new(pAlloc) AnimCallbackBridge<T>(pObj, func);
	}
}