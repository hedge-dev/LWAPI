#pragma once

namespace app::animation
{
	class CharactorAnimation;
	
	class AnimationCallback : public fnd::ReferencedObject
	{
	public:
		virtual void Callback(CharactorAnimation* in_pAnimation, ETriggerValueType in_type, CallbackParam in_param) = 0;
	};

	template<class T>
	class AnimCallbackBridge : public AnimationCallback
	{
	public:
		typedef void (T::*MemFunc)(CharactorAnimation* in_pAnimation, ETriggerValueType in_type, CallbackParam in_param);
		
	protected:
		T* m_pObj{};
		MemFunc m_pFunc{};

	public:
		AnimCallbackBridge(T* in_pObj, MemFunc in_func) : m_pObj(in_pObj), m_pFunc(in_func)
		{
			
		}
		
		void Callback(CharactorAnimation* in_pAnimation, ETriggerValueType in_type, CallbackParam in_param) override
		{
			(m_pObj->*m_pFunc)(in_pAnimation, in_type, in_param);
		}
	};
	
	template<class T>
	AnimationCallback* CreateAnimCallback(T* in_pObj, typename AnimCallbackBridge<T>::MemFunc in_func, csl::fnd::IAllocator* in_pAlloc)
	{
		return new(in_pAlloc) AnimCallbackBridge<T>(in_pObj, in_func);
	}
}