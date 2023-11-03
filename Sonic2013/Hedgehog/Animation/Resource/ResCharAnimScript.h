#pragma once

// Heavily based on https://gist.github.com/Sajidur78/bf1012ebad9dfab27a0986715d56d0d2
namespace app::animation
{
	enum EAnimationType : ushort
	{
		eAnimationType_Simple,
		eAnimationType_Complex,
	};

	enum EAnimOptions
	{
		eAnimOptions_Stop = 0,
		eAnimOptions_Loop = 1,
		eAnimOptions_Mirror = 4,
	};

	enum EPlayMode
	{
		ePlayMode_Loop,
		ePlayMode_Stop
	};

	enum EInterpolateMode
	{
		eInterpolateMode_Immediate,
		eInterpolateMode_StopPlay,
		eInterpolateMode_StopStop,
		eInterpolateMode_FinishStop,
		eInterpolateMode_PlayPlay,
		eInterpolateMode_PlayStop,
		eInterpolateMode_FinishPlay,
		eInterpolateMode_Synchronize,
	};

	enum ETriggerValueType
	{
		eTriggerValueType_Enum,
		eTriggerValueType_Int,
		eTriggerValueType_Float,
		eTriggerValueType_String
	};

	struct PlayModeInfo
	{
		EPlayMode Mode;
		short RandomMin;
		short RandomMax;
	};

	struct BlendAddNode
	{
		const char* pName;
		float Weight;
		int Priority;
	};

	// Size is 20
	struct BlenderDef
	{
		size_t StructType{ 1 }; // Always 1
		const char* pName;
		float Weight;
		size_t NodeCount;
		BlendAddNode* pNodes;
	};

	struct BlenderData
	{
		size_t StructType{ 1 }; // Always 1
		size_t BlenderCount;
		BlenderDef** ppBlenders;

		bool IsValid() const
		{
			return StructType == 1;
		}
	};

	struct SeqData
	{
		const char* pName;
	};

	struct SequenceTable
	{
		size_t StructType{ 0 }; // Always 0
		PlayModeInfo PlayMode;
		size_t SequenceCount;
		SeqData* pSequences;

		bool IsValid() const
		{
			return !StructType;
		}
	};

	struct TransitionInfo
	{
		const char* pFrom;
		const char* pTo;
	};

	struct TransitionArray
	{
		size_t Count;
		TransitionInfo* pTransitions;
	};

	struct InterpolateInfo
	{
		EInterpolateMode Unk1; // Enter interpolation?
		EInterpolateMode Unk2; // Exit interpolation?
		float Time;
		const char* From;
	};

	struct InterpolateArray
	{
		size_t Count;
		InterpolateInfo* Interpolations;
	};

	typedef union
	{
		int Int;
		float Float;
		const char* String;
	} CallbackParam;

	struct TriggerInfo
	{
		float Frame;
		uint ID;
		ETriggerValueType ValueType;
		CallbackParam Value;
	};

	struct TriggerInfoArray
	{
		size_t Count;
		TriggerInfo* pEvents;
	};

	struct AnimationDef
	{
		const char* pName;
		EAnimationType Type;
		short Layer;
	};

	struct PlayData
	{
		float StartFrame;
		float EndFrame;
		float Speed;
		PlayModeInfo PlayInfo;
		EAnimOptions Options;
		InterpolateArray Interpolations;
	};

	struct SimpleDef : AnimationDef
	{
		const char* pResource;
		PlayData Data;
		TriggerInfoArray Callbacks;
	};

	struct ComplexData
	{
		union
		{
			BlenderData BlenderInfo;
			SequenceTable SequenceInfo;
		};
	};

	struct SimpleAnimationArray
	{
		size_t Count;
		SimpleDef* pAnimations;
	};

	struct ComplexDef : AnimationDef
	{
		SimpleAnimationArray Animations;
		ComplexData* pData;
	};

	struct ComplexAnimationArray
	{
		size_t Count;
		ComplexDef* pAnimations;
	};

	struct AnimationDefArray
	{
		SimpleAnimationArray SimpleAnimations;
		ComplexAnimationArray ComplexAnimations;
	};

	class FileHeader
	{
	protected:
		const char* m_pSignature{ "ANIM" };
		const char* m_pVersion{ "1.02" };
	public:
		ushort LayerCount{};
		ushort TriggerCount{};
		AnimationDefArray* pAnimations{};
		TransitionArray* pTransitions{};
	};

	class ResCharAnimScriptData
	{
	public:
		FileHeader* pHeader{};
		csl::fnd::IAllocator* pAllocator{};
	};
}

namespace app
{
	class ResCharAnimScript : public hh::ut::ResCommon<animation::ResCharAnimScriptData>
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F60FC8));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	namespace animation
	{
		class ResCharAnim : public hh::ut::ResCommon<hh::gfx::res::ResAnimSkeletonData>
		{
		public:
			ResCharAnim& operator =(hh::gfx::res::ResAnimSkeleton in_anim)
			{
				m_pRes = &in_anim.ref();
				return *this;
			}
		};
	}
}