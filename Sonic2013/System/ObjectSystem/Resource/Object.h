#pragma once

namespace app
{
	namespace SetEd
	{
		class SResClassData
		{

		};

		class CResClass : public fnd::ResCommon<SResClassData>
		{

		};

		// Maybe this is somewhat big
		class SResObjectData
		{
		public:
			uint m_ObjectID;
			void* m_Unk1;
			CResClass m_Class;
			float m_Interval;
			float m_RangeIn;
			float m_RangeOut;
			uint m_ParentID;
			void* m_Unk3;

		public:
			uint GetUID() const
			{
				return m_ObjectID & 0xFFFF;
			}

			uint GetParentID() const
			{
				return m_ParentID;
			}
		};

		class CResObject : public fnd::ResCommon<SResObjectData>
		{

		};
	}
}