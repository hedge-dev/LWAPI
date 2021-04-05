#pragma once

namespace app
{
	namespace SetEd
	{
		// Maybe this is somewhat big
		class CResObjectData
		{
			uint m_ObjectID;
			void* m_Unk1;
			csl::math::Vector3 m_Position;
			void* m_Unk2;
			uint m_ParentID;
			void* m_Unk3;

		public:
			uint GetID() const
			{
				return m_ObjectID;
			}

			uint GetParentID() const
			{
				return m_ParentID;
			}

			const csl::math::Vector3& GetPosition() const
			{
				return m_Position;
			}
		};

		class CResObject : public fnd::ResCommon<CResObjectData>
		{

		};
	}

	class CSetObjectListener;
	class CSetObject : public hh::base::CRefCountObject
	{
	public:
		inline static FUNCTION_PTR(CSetObjectListener*, __thiscall, ms_fpGetNthObject, ASLR(0x00841400), const CSetObject*, size_t);
		
		void* m_Unk1{};
		SetEd::CResObject m_Object{ nullptr };
		void* m_pUnk2{};
		
		CSetObject()
		{
			
		}

		CSetObjectListener* GetNthObject(size_t n)
		{
			return ms_fpGetNthObject(this, n);
		}
	};
}