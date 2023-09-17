#pragma once

namespace SurfRide
{
	template <typename T>
	class ReferenceCount : public Base
	{
	private:
		T* m_pX{};

	public:
		ReferenceCount()
		{
			m_pX = nullptr;
		}

		ReferenceCount(const ReferenceCount<T>& in_rcOther)
		{
			m_pX = in_rcOther.m_pX;
			if (m_pX)
				m_pX->IncrementReferenceCount();
		}

		ReferenceCount(T* in_pX)
		{
			m_pX = in_pX;
			if (m_pX)
				m_pX->IncrementReferenceCount();
		}

		~ReferenceCount()
		{
			Reset();
		}

		void Reset()
		{
			if (m_pX)
			{
				m_pX->DecrementReferenceCount();
				if (!m_pX->GetReferenceCount())
				{
					m_pX->Cleanup();

					delete m_pX;
				}
			}
			
			m_pX = nullptr;
		}

		T* Get() const
		{
			return m_pX;
		}

		T* operator->() const
		{
			return m_pX;
		}

		T& operator*() const
		{
			return *m_pX;
		}

		operator bool() const
		{
			return m_pX;
		}

		ReferenceCount<T>& operator=(const ReferenceCount<T>& in_rcOther)
		{
			Reset();

			m_pX = in_rcOther.m_pX;
			
			if (m_pX)
				m_pX->IncrementReferenceCount();

			return *this;
		}
	};
}