#pragma once

namespace csl::fnd
{
	class DelegateAllocator : csl::fnd::IAllocator
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
	
	template<typename Ret, typename Alloc>
	class Delegate;
	
	template<typename Alloc, typename... Args>
	class Delegate<void(Args...), Alloc>
	{
		typedef void function(Args...);
		
	protected:
		class DelegateFunctorBase
		{
		public:
			DelegateFunctorBase* m_PrevFunctor{};
			
			virtual ~DelegateFunctorBase() = default;
			virtual void Invoke(Args... args) = 0;
		};

		// This is a custom class, it shouldn't be used a reference for LW's DelegateFunctor
		class DelegateFunctor : public DelegateFunctorBase
		{
		public:
			void* m_pInstance;
			function* m_pFunction{};
			
			virtual void Invoke(Args... args) override
			{
				m_pFunction(args...);
			}
		};
		
		DelegateFunctorBase* m_pFunctor;
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
				
				delete pCurFunctor;
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

		void Connect(function& pFunction)
		{
			void* pMem = m_Allocator.Alloc(sizeof(DelegateFunctor), alignof(DelegateFunctor));
			DelegateFunctor* pFunctor = new(pMem) DelegateFunctor();
			pFunctor->m_pFunction = &pFunction;
			pFunctor->m_PrevFunctor = m_pFunctor;
			
			m_pFunctor = pFunctor;
		}

		void Remove(function& pFunction)
		{
			DelegateFunctor* pCurFunctor = reinterpret_cast<DelegateFunctor*>(m_pFunctor);
			DelegateFunctor* pNextFunctor = nullptr;
			
			while (pCurFunctor)
			{
				pNextFunctor = reinterpret_cast<DelegateFunctor*>(pCurFunctor->m_PrevFunctor);

				if (pCurFunctor->m_pFunction == &pFunction)
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

		Delegate& operator+=(function& rFunction)
		{
			Connect(rFunction);
			return *this;
		}

		Delegate& operator-=(function& rFunction)
		{
			Remove(rFunction);
			return *this;
		}

		void operator()(Args... args)
		{
			Invoke(args...);
		}
	};
}