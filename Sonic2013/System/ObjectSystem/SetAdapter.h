#pragma once

namespace app
{
	class CSetObjectListener;
	class CSetAdapterMgr;

	inline static int ShiftOfUserData(uint in_type) { return 8 * in_type + 16; }

	class CSetAdapter
	{
	protected:
		CSetAdapterMgr* m_pAdapterManager;
		CSetObjectListener* m_pListener;
		SetEd::CResObject m_pObject;
		Gops::CActor* m_pActor;
		uint m_StatusFlags;
		float m_RetireTime;
		
	public:
		CSetObjectListener* GetListener() const
		{
			return m_pListener;
		}
		
		void SetListener(CSetObjectListener* in_pListener)
		{
			m_pListener = in_pListener;
		}

		uint GetStatusFlags() const
		{
			return m_StatusFlags;
		}

		uint GetUserData(uint in_type) const
		{
			uint shift = ShiftOfUserData(in_type);
			return (m_StatusFlags & (255 << shift)) >> shift;
		}
		
		void SetStatusFlags(uint in_flag)
		{
			m_StatusFlags |= in_flag;
		}

		void SetUserData(uint in_type, uint in_value)
		{
			uint shift = ShiftOfUserData(in_type);
			m_StatusFlags = m_StatusFlags & ~(255 << shift) | (in_value << shift) & (255 << shift);
		}

		const SetEd::CResObject& GetObjectResource() const
		{
			return m_pObject;
		}

		Gops::CActor* GetActor() const
		{
			return m_pActor;
		}

		const char* GetName() const
		{
			return m_pObject.GetName();
		}

		template <typename T>
		T* GetData() const
		{
			if (m_pObject.IsValid())
				return reinterpret_cast<T*>(m_pObject.GetParamAddress());
			
			return nullptr;
		}

		const csl::math::Vector3& GetPosition() const
		{
			return m_pObject.GetUnit(m_pObject.ref().Class.ref().Unk1).GetPosition();
		}

		const csl::math::Quaternion& GetRotation() const
		{
			csl::math::Quaternion q = SetEd::CalcRotationByAngle(m_pObject.GetUnit(m_pObject.ref().Class.ref().Unk1).GetRotation());
			return q;
		}
		
		static CSetAdapter* GetPointerFromActor(const Gops::CActor& in_pActor)
		{
			return in_pActor.GetAdapter();
		}
	};
}