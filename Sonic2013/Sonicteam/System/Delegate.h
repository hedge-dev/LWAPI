#pragma once

namespace csl::fnd
{
	class DelegateAllocator : public csl::fnd::IAllocator
	{
	public:
		void* Alloc(size_t in_size, int in_alignment) override
		{
			return operator new(in_size);
		}

		void Free(void* in_pLoc) override
		{
			return operator delete(in_pLoc);
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
			DelegateFunctorBase* PrevFunctor{};
			
			virtual ~DelegateFunctorBase() = default;
			virtual void Invoke(Args... in_args) = 0;
		};
		
		template<typename TInstance, typename... Args>
		class DelegateFunctor : public DelegateFunctorBase
		{
		public:
			typedef void (TInstance::*MemFunc)(Args...);

			TInstance* pInstance;
			MemFunc pMemFunc{};
			
			virtual void Invoke(Args... in_args) override
			{
				(pInstance->*pMemFunc)(in_args...);
			}
		};
		
		DelegateFunctorBase* m_pFunctor{};
		Alloc m_Allocator{};

		void FreeFunctorList(DelegateFunctorBase* in_pFunctor)
		{
			if (!in_pFunctor)
				return;

			DelegateFunctorBase* pLastFunctor = nullptr;
			DelegateFunctorBase* pCurFunctor = in_pFunctor;
			
			while (pCurFunctor)
			{
				pLastFunctor = pCurFunctor->PrevFunctor;
				
				pCurFunctor->~DelegateFunctorBase();
				m_Allocator.Free(pCurFunctor);
				
				pCurFunctor = pLastFunctor;
			}
		}

		void InvokeFunctorList(DelegateFunctorBase* in_pFunctor, Args... in_args)
		{
			if (in_pFunctor)
			{
				if (in_pFunctor->PrevFunctor)
					InvokeFunctorList(in_pFunctor->PrevFunctor, in_args...);

				in_pFunctor->Invoke(in_args...);
			}
		}
		
	public:
		virtual ~Delegate()
		{
			FreeFunctorList(m_pFunctor);
		}

		template<class TInstance>
		void Connect(TInstance* in_pInst, typename DelegateFunctor<TInstance, Args...>::MemFunc in_pFunc)
		{
			void* pMem = m_Allocator.Alloc(sizeof(DelegateFunctor<TInstance, Args...>), alignof(DelegateFunctor<TInstance, Args...>));
			DelegateFunctor<TInstance, Args...>* pFunctor = new(pMem) DelegateFunctor<TInstance, Args...>();
			pFunctor->pInstance = in_pInst;
			pFunctor->pMemFunc = in_pFunc;
			pFunctor->PrevFunctor = m_pFunctor;
			
			m_pFunctor = pFunctor;
		}

		template<class TInstance>
		void Remove(TInstance* in_pInst, typename DelegateFunctor<TInstance, Args...>::MemFunc in_pFunc)
		{
			DelegateFunctor<TInstance, Args...>* pCurFunctor = reinterpret_cast<DelegateFunctor<TInstance, Args...>*>(m_pFunctor);
			DelegateFunctor<TInstance, Args...>* pNextFunctor = nullptr;
			
			while (pCurFunctor)
			{
				pNextFunctor = reinterpret_cast<DelegateFunctor<TInstance, Args...>*>(pCurFunctor->PrevFunctor);

				if (pCurFunctor->pMemFunc == in_pFunc && pCurFunctor->pInstance == in_pInst)
				{
					pCurFunctor->~DelegateFunctor();
					m_Allocator.Free(pCurFunctor);
					m_pFunctor = pNextFunctor;
					return;
				}

				pCurFunctor = pNextFunctor;
			}
		}
		
		void Invoke(Args... in_args)
		{
			if (m_pFunctor)
			{
				if (m_pFunctor->PrevFunctor)
					InvokeFunctorList(m_pFunctor->PrevFunctor, in_args...);

				m_pFunctor->Invoke(in_args...);
			}
		}

		template<class T>
		Delegate& operator+=(ut::Pair<T*, typename DelegateFunctor<T, Args...>::MemFunc> in_item)
		{
			Connect(in_item.Key, in_item.X);
			return *this;
		}

		template<class T>
		Delegate& operator-=(ut::Pair<T*, typename DelegateFunctor<T, Args...>::MemFunc> in_item)
		{
			Remove(in_item.Key, in_item.X);
			return *this;
		}

		void operator()(Args... in_args)
		{
			Invoke(in_args...);
		}
	};
}