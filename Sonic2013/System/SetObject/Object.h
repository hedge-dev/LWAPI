#pragma once

namespace app::SetEd
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