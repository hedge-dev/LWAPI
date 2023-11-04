#pragma once

namespace app
{
	namespace SetEd
	{
		union ParamData
		{
			char ByteVal;
			const char* StrVal;
			uint UnsignedIntVal;
			int IntVal;
		};

		// This is probably the wrong way of doing it
		struct SParamDescData
		{
			ushort ParamType;
			ushort ParamOffset;
			const char* pParamName;
			const char* pParamDesc;
			ParamData DefaultValue;
			ParamData ValueStep;
			ParamData MaxValue;
			ParamData MinValue;
		};
		
		struct SResClassData
		{
			size_t Flags;
			size_t CRC;
			const char* pName;
			const char* pCategory;
			size_t Unk1;
			float DefaultRangeOut;
			float DefaultRangeIn;
			app::TArray<SParamDescData, app::dbg::Allocator<SParamDescData>> Params;
		};

		class CResClass : public CResCommon<SResClassData>
		{
		public:
			uint GetParamSize() const
			{
				return ref().Flags & 0xFFFF;
			}

			bool IsPlain() const
			{
				return (ref().Flags >> 30) & 1;
			}

			const char* GetName() const
			{
				return ref().pName;
			}

			const char* GetCategory() const
			{
				return ref().pCategory;
			}
		};

		struct SResUnitData
		{
			float PosX;
			float PosY;
			float PosZ;
			csl::math::Angle3 Rotation;

			float LocalPosX;
			float LocalPosY;
			float LocalPosZ;
			csl::math::Angle3 LocalRotation;
		};

		class CResUnit : public CResCommon<SResUnitData>
		{
		public:
			const csl::math::Vector3& GetPosition() const
			{
				return *reinterpret_cast<const csl::math::Vector3*>(&ref().PosX);
			}

			const csl::math::Angle3& GetRotation() const
			{
				return ref().Rotation;
			}

			const csl::math::Vector3& GetLocalPosition() const
			{
				return *reinterpret_cast<const csl::math::Vector3*>(&ref().LocalPosX);
			}

			const csl::math::Angle3& GetLocalRotation() const
			{
				return ref().LocalRotation;
			}
		};
		
		struct SResObjectData
		{
			uint ObjectID; // Actually flags
			uint ClassCRC;
			CResClass Class;
			float Interval;
			float RangeIn;
			float RangeOut;
			uint ParentID;
			app::TArray<SResUnitData, app::dbg::Allocator<SResUnitData>> Units;
			INSERT_PADDING(8) {};
			void* pParam;
		};

		class CResObject : public CResCommon<SResObjectData>
		{
		public:
			CResClass GetClass() const
			{
				return ref().Class;
			}

			size_t GetClassHash() const
			{
				return ref().ClassCRC;
			}

			size_t GetUnitNum()
			{
				return ref().Units.size();
			}
			
			CResUnit GetUnit(size_t in_unit) const
			{
				return CResUnit{ const_cast<SResUnitData*>(&ref().Units[in_unit]) };
			}

			uint GetUID() const
			{
				return ref().ObjectID & 0xFFFF;
			}

			// None
			// Ground
			// Guide
			// Grind
			// SV
			// Circle
			// Ground2
			char GetAlignment() const
			{
				return (ref().ObjectID & 0xF000000) >> 24;
			}

			// Front
			// Side
			// Up
			char GetLayout() const
			{
				return (ref().ObjectID & 0xF00000) >> 20;
			}

			uint GetParentID() const
			{
				return ref().ParentID;
			}

			const char* GetName() const
			{
				return ref().Class->pName;
			}

			void* GetParamAddress() const
			{
				return const_cast<void**>(&ref().pParam);
			}
		};

		inline csl::math::Quaternion CalcRotationByAngle(const csl::math::Angle3& in_angle)
		{
			csl::math::Quaternion q
			(
				Eigen::AngleAxisf(in_angle.x(), csl::math::Angle3::UnitX())
				* Eigen::AngleAxisf(in_angle.y(), csl::math::Angle3::UnitY())
				* Eigen::AngleAxisf(in_angle.z(), csl::math::Angle3::UnitZ())
			);

			return q;
		}
	}
}