#pragma once

namespace app::fnd
{
	using namespace csl::ut;
	
	class RflClass;
	class RflClassEnum;
	
	class RflClassMember
	{
		enum Type : char
		{
			TYPE_VOID,
			TYPE_BOOL,
			TYPE_SINT8,
			TYPE_UINT8,
			TYPE_SINT16,
			TYPE_UINT16,
			TYPE_SINT32,
			TYPE_UINT32,
			TYPE_SINT64,
			TYPE_UINT64,
			TYPE_FLOAT,
			TYPE_VECTOR3,
			TYPE_VECTOR4,
			TYPE_QUATERNION,
			TYPE_MATRIX34,
			TYPE_MATRIX44,
			TYPE_POINTER,
			TYPE_ARRAY,
			TYPE_SIMPLE_ARRAY,
			TYPE_ENUM,
			TYPE_STRUCT,
			TYPE_FLAGS,
			TYPE_CSTRING,
			TYPE_STRING,
			TYPE_OBJECT_ID,
			TYPE_POSITION
		};

		struct Metadata
		{
			Type m_type;
			const char* p_name;
			uint8 m_byteSize;
			uint8 m_alignment;
		};

		static const Metadata ms_typeMetadata[];
		
	protected:
		const char* p_name{};
		RflClass* p_struct{};
		RflClassEnum* p_enum{};
		Enum<Type, uint8> m_type{};
		Enum<Type, uint8> m_underlyingType{};
		uint16 m_arrayLength{};
		Bitset<uint16> m_flags{};
		uint16 m_memberOffset{};
		RflCustomAttributes* p_attributes{};

	public:
		[[nodiscard]] const char* GetName() const
		{
			return p_name;
		}

		[[nodiscard]] const RflClass* GetClass() const
		{
			return p_struct;
		}
		
		[[nodiscard]] const RflClass* GetStructClass() const
		{
			return p_struct;
		}

		[[nodiscard]] const RflClassEnum* GetEnumClass() const
		{
			return p_enum;
		}

		[[nodiscard]] size_t GetCstyleArraySize() const
		{
			return m_arrayLength;
		}

		[[nodiscard]] const RflCustomAttribute* GetAttribute(const char* name) const
		{
			return p_attributes->GetAttribute(name);
		}

		[[nodiscard]] Type GetType() const
		{
			return m_type;
		}

		[[nodiscard]] Type GetSubType() const
		{
			return m_underlyingType;
		}

		[[nodiscard]] size_t GetByteOffset() const
		{
			return m_memberOffset;
		}
		
		[[nodiscard]] size_t GetSizeInBytes() const;
	};

#define DEFINE_METADATA_FULL(id, type, size, align) Metadata { id, type, (uint8)(size), (uint8)(align) }
#define DEFINE_METADATA_WITH_NAME(id, name, type) Metadata { id, name, sizeof(type), alignof(type) }
#define DEFINE_METADATA(id, type) Metadata { id, #type, sizeof(type), alignof(type) }
#define DEFINE_DUMMY_METADATA(id, type) Metadata { id, #type, (uint8)-1, (uint8)-1 }
	
	inline const RflClassMember::Metadata RflClassMember::ms_typeMetadata[] = 
	{
		DEFINE_DUMMY_METADATA(TYPE_VOID, void),
		DEFINE_METADATA(TYPE_BOOL, bool),
		DEFINE_METADATA(TYPE_SINT8, sint8),
		DEFINE_METADATA(TYPE_UINT8, uint8),
		DEFINE_METADATA(TYPE_SINT16, sint16),
		DEFINE_METADATA(TYPE_UINT16, uint16),
		DEFINE_METADATA(TYPE_SINT32, sint32),
		DEFINE_METADATA(TYPE_UINT32, uint32),
		DEFINE_METADATA(TYPE_SINT64, sint64),
		DEFINE_METADATA(TYPE_UINT64, uint64),
		DEFINE_METADATA(TYPE_FLOAT, float),
		DEFINE_METADATA_WITH_NAME(TYPE_VECTOR3, "vector3", csl::math::Vector3),
		DEFINE_METADATA_WITH_NAME(TYPE_VECTOR4, "vector4", csl::math::Vector4),
		DEFINE_METADATA_WITH_NAME(TYPE_QUATERNION, "quaternion", csl::math::Quaternion),
		DEFINE_METADATA_WITH_NAME(TYPE_MATRIX34, "matrix34", csl::math::Matrix34),
		DEFINE_METADATA_WITH_NAME(TYPE_MATRIX44, "matrix44", csl::math::Matrix44),
		DEFINE_METADATA_WITH_NAME(TYPE_POINTER, "pointer", void*),
		DEFINE_METADATA_FULL(TYPE_ARRAY, "array", sizeof(csl::ut::Array<void>), -1),
		DEFINE_METADATA_FULL(TYPE_SIMPLE_ARRAY, "simplearray", 8, -1),
		DEFINE_METADATA_FULL(TYPE_ENUM, "enum", -1, -1),
		DEFINE_METADATA_FULL(TYPE_STRUCT, "struct", -1, -1),
		DEFINE_METADATA_FULL(TYPE_FLAGS, "flags", -1, -1),
		DEFINE_METADATA_WITH_NAME(TYPE_CSTRING, "cstring", char*),
		DEFINE_METADATA_WITH_NAME(TYPE_STRING, "string", csl::ut::VariableString),
		DEFINE_METADATA_WITH_NAME(TYPE_OBJECT_ID, "csetobjectid", uint),
		DEFINE_METADATA_FULL(TYPE_POSITION, "position", 0xC, 4),
	};

#undef DEFINE_METADATA_WITH_NAME
#undef DEFINE_DUMMY_METADATA
#undef DEFINE_METADATA_FULL
#undef DEFINE_METADATA
}

#include "hhRflClass.h"

inline size_t app::fnd::RflClassMember::GetSizeInBytes() const
{
	const uint8 type = m_type;
	const uint8 underlyingType = m_underlyingType;
	
	switch (type)
	{
	case TYPE_VOID:
		return 0;

	case TYPE_ARRAY:
	{
		size_t underlyingSize = 1;
		if (underlyingType == TYPE_STRUCT)
			underlyingSize = GetStructClass()->GetSizeInBytes();
		else
			underlyingSize = ms_typeMetadata[underlyingType].m_byteSize;

		if (GetCstyleArraySize())
			return ms_typeMetadata[underlyingType].m_byteSize * underlyingSize * GetCstyleArraySize();
			
		return ms_typeMetadata[underlyingType].m_byteSize * underlyingSize;
	}

	case TYPE_STRUCT:
		return GetStructClass()->GetSizeInBytes();

	case TYPE_ENUM:
	case TYPE_FLAGS:
		return ms_typeMetadata[underlyingType].m_byteSize;
		
	default:
		return ms_typeMetadata[type].m_byteSize;
	}
}