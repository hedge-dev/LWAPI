#pragma once

namespace app
{
	namespace SetEd
	{
		union ParamData
		{
			char m_ByteVal;
			const char* m_StrVal;
			uint m_UnsignedIntVal;
			int m_IntVal;
		};

		// This is probably the wrong way of doing it
		struct SParamDescData
		{
			ushort m_ParamType;
			ushort m_ParamOffset;
			const char* m_pParamName;
			const char* m_pParamDesc;
			ParamData m_DefaultValue;
			ParamData m_ValueStep;
			ParamData m_MaxValue;
			ParamData m_MinValue;
		};
		
		struct SResClassData
		{
			size_t m_Flags;
			size_t m_CRC;
			const char* m_pName;
			const char* m_pCategory;
			void* m_Unk1;
			float m_DefaultRangeIn;
			float m_DefaultRangeOut;
			app::TArray<SParamDescData, app::dbg::Allocator<SParamDescData>> m_Params;
		};

		class CResClass : public fnd::ResCommon<SResClassData>
		{
		public:
			const char* GetName() const
			{
				return ref().m_pName;
			}

			const char* GetCategory() const
			{
				return ref().m_pCategory;
			}
		};

		struct SResUnitData
		{
			float m_PosX;
			float m_PosY;
			float m_PosZ;
			csl::math::Angle3 m_Rotation;

			float m_LocalPosX;
			float m_LocalPosY;
			float m_LocalPosZ;
			csl::math::Angle3 m_LocalRotation;
		};

		class CResUnit : public fnd::ResCommon<SResUnitData>
		{
		public:
			const csl::math::Vector3& GetPosition() const
			{
				return *reinterpret_cast<const csl::math::Vector3*>(&ref().m_PosX);
			}

			const csl::math::Angle3& GetRotation() const
			{
				return ref().m_Rotation;
			}

			const csl::math::Vector3& GetLocalPosition() const
			{
				return *reinterpret_cast<const csl::math::Vector3*>(&ref().m_LocalPosX);
			}

			const csl::math::Angle3& GetLocalRotation() const
			{
				return ref().m_LocalRotation;
			}
		};
		
		struct SResObjectData
		{
			uint m_ObjectID; // Actually flags
			uint m_ClassCRC;
			CResClass m_Class;
			float m_Interval;
			float m_RangeIn;
			float m_RangeOut;
			uint m_ParentID;
			app::TArray<SResUnitData, app::dbg::Allocator<SResUnitData>> m_Units;
			INSERT_PADDING(8) {};
			void* m_pParam;
		};

		class CResObject : public fnd::ResCommon<SResObjectData>
		{
		public:
			CResClass GetClass() const
			{
				return ref().m_Class;
			}

			size_t GetClassHash() const
			{
				return ref().m_ClassCRC;
			}

			size_t GetUnitNum()
			{
				return ref().m_Units.size();
			}
			
			CResUnit GetUnit(size_t unit) const
			{
				return CResUnit{ const_cast<SResUnitData*>(&ref().m_Units[unit]) };
			}
			
			uint GetUID() const
			{
				return ref().m_ObjectID & 0xFFFF;
			}

			uint GetParentID() const
			{
				return ref().m_ParentID;
			}

			const char* GetName() const
			{
				return ref().m_Class->m_pName;
			}

			void* GetParamAddress() const
			{
				return const_cast<void**>(&ref().m_pParam);
			}
		};
	}
}