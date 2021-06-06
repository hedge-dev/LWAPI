#pragma once

namespace csl::fnd
{
	class DelegateAllocator : public csl::fnd::IAllocator
	{
	public:
		void* Alloc(size_t size, int alignment) override
		{
			return operator new(size);
		}

		void Free(void* loc) override
		{
			return operator delete(loc);
		}
	};
	
	template<typename Args, typename Alloc = DelegateAllocator>
	class Delegate;
	
	template<typename Alloc, typename... Args>
	class Delegate<void(Args...), Alloc>
	{
	protected:
		class DelegateFunctorBase
		{
		public:
			DelegateFunctorBase* m_PrevFunctor{};
			
			virtual ~DelegateFunctorBase() = default;
			virtual void Invoke(Args... args) = 0;
		};
		
		template<typename TInstance, typename... Args>
		class DelegateFunctor : public DelegateFunctorBase
		{
		public:
			typedef void (TInstance::*MemFunc)(Args...);

			TInstance* m_pInstance;
			MemFunc m_pMemFunc{};
			
			virtual void Invoke(Args... args) override
			{
				(m_pInstance->*m_pMemFunc)(args...);
			}
		};
		
		DelegateFunctorBase* m_pFunctor{};
		Alloc m_Allocator{};

		void FreeFunctorList(DelegateFunctorBase* pFunctor)
		{
			if (!pFunctor)
				return;

			DelegateFunctorBase* pLastFunctor = nullptr;
			DelegateFunctorBase* pCurFunctor = pFunctor;
			
			while (pCurFunctor)
			{
				pLastFunctor = pCurFunctor->m_PrevFunctor;
				
				pCurFunctor->~DelegateFunctorBase();
				m_Allocator.Free(pCurFunctor);
				
				pCurFunctor = pLastFunctor;
			}
		}

		void InvokeFunctorList(DelegateFunctorBase* pFunctor, Args... args)
		{
			if (pFunctor)
			{
				if (pFunctor->m_PrevFunctor)
					InvokeFunctorList(pFunctor->m_PrevFunctor, args...);

				pFunctor->Invoke(args...);
			}
		}
		
	public:
		virtual ~Delegate()
		{
			FreeFunctorList(m_pFunctor);
		}

		template<class TInstance>
		void Connect(TInstance* pInst, typename DelegateFunctor<TInstance, Args...>::MemFunc pFunc)
		{
			void* pMem = m_Allocator.Alloc(sizeof(DelegateFunctor<TInstance, Args...>), alignof(DelegateFunctor<TInstance, Args...>));
			DelegateFunctor<TInstance, Args...>* pFunctor = new(pMem) DelegateFunctor<TInstance, Args...>();
			pFunctor->m_pInstance = pInst;
			pFunctor->m_pMemFunc = pFunc;
			pFunctor->m_PrevFunctor = m_pFunctor;
			
			m_pFunctor = pFunctor;
		}

		template<class TInstance>
		void Remove(TInstance* pInst, typename DelegateFunctor<TInstance, Args...>::MemFunc pFunc)
		{
			DelegateFunctor<TInstance, Args...>* pCurFunctor = reinterpret_cast<DelegateFunctor<TInstance, Args...>*>(m_pFunctor);
			DelegateFunctor<TInstance, Args...>* pNextFunctor = nullptr;
			
			while (pCurFunctor)
			{
				pNextFunctor = reinterpret_cast<DelegateFunctor<TInstance, Args...>*>(pCurFunctor->m_PrevFunctor);

				if (pCurFunctor->m_pMemFunc == pFunc && pCurFunctor->m_pInstance == pInst)
				{
					pCurFunctor->~DelegateFunctor();
					m_Allocator.Free(pCurFunctor);
					m_pFunctor = pNextFunctor;
					return;
				}

				pCurFunctor = pNextFunctor;
			}
		}
		
		void Invoke(Args... args)
		{
			if (m_pFunctor)
			{
				if (m_pFunctor->m_PrevFunctor)
					InvokeFunctorList(m_pFunctor->m_PrevFunctor, args...);

				m_pFunctor->Invoke(args...);
			}
		}

		template<class T>
		Delegate& operator+=(ut::Pair<T*, typename DelegateFunctor<T, Args...>::MemFunc> item)
		{
			Connect(item.key, item.x);
			return *this;
		}

		template<class T>
		Delegate& operator-=(ut::Pair<T*, typename DelegateFunctor<T, Args...>::MemFunc> item)
		{
			Remove(item.key, item.x);
			return *this;
		}

		void operator()(Args... args)
		{
			Invoke(args...);
		}
	};
}