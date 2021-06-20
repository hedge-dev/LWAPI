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
		EPlayMode m_Mode;
		short m_RandomMin;
		short m_RandomMax;
	};

	struct BlendAddNode
	{
		const char* m_pName;
		float m_Weight;
		int m_Priority;
	};

	// Size is 20
	struct BlenderDef
	{
		size_t m_StructType; // Always 1
		const char* m_pName;
		float m_Weight;
		size_t m_NodeCount;
		BlendAddNode* m_pNodes;
	};

	struct BlenderData
	{
		size_t m_StructType; // Always 1
		size_t m_BlenderCount;
		BlenderDef** m_ppBlenders;

		bool IsValid() const
		{
			return m_StructType == 1;
		}
	};

	struct SeqData
	{
		const char* m_pName;
	};

	struct SequenceTable
	{
		size_t m_StructType; // Always 0
		PlayModeInfo m_PlayMode;
		size_t m_SequenceCount;
		SeqData* m_pSequences;

		bool IsValid() const
		{
			return !m_StructType;
		}
	};

	struct TransitionInfo
	{
		const char* m_pFrom;
		const char* m_pTo;
	};

	struct TransitionTable
	{
		size_t m_Count;
		TransitionInfo* m_pTransitions;
	};

	struct InterpolateInfo
	{
		EInterpolateMode m_Unk1; // Enter interpolation?
		EInterpolateMode m_Unk2; // Exit interpolation?
		float m_Time;
		const char* m_From;
	};

	struct InterpolateArray
	{
		size_t m_Count;
		InterpolateInfo* m_Interpolations;
	};

	typedef union
	{
		int m_Int;
		float m_Float;
		const char* m_String;
	} CallbackParam;

	struct TriggerInfo
	{
		float m_Frame;
		uint m_ID;
		ETriggerValueType m_ValueType;
		CallbackParam m_Value;
	};

	struct TriggerInfoArray
	{
		size_t m_Count;
		TriggerInfo* m_pEvents;
	};

	struct AnimationDef
	{
		const char* m_pName;
		EAnimationType m_Type;
		short m_Layer;
	};
	
	struct SimpleDef : AnimationDef
	{
		const char* m_pResource;
		float m_StartFrame;
		float m_EndFrame;
		float m_Speed;
		PlayModeInfo m_PlayInfo;
		EAnimOptions m_Options;
		InterpolateArray m_Interpolations;
		TriggerInfoArray m_Callbacks;
	};

	struct ComplexData
	{
		union
		{
			BlenderData m_BlenderInfo;
			SequenceTable m_SequenceInfo;
		};
	};

	struct SimpleAnimationArray
	{
		size_t m_AnimationCount;
		SimpleDef* m_pAnimations;
	};

	struct ComplexDef : AnimationDef
	{
		SimpleAnimationArray m_Animations;
		ComplexData* m_pData;
	};

	struct ComplexAnimationArray
	{
		size_t m_Count;
		ComplexDef* m_pComplexAnimations;
	};

	struct AnimationDefArray
	{
		SimpleAnimationArray m_SimpleAnimations;
		ComplexAnimationArray m_ComplexAnimations;
	};

	class ResCharAnimScriptData
	{
	protected:
		const char* m_pSignature;
		const char* m_pVersion;
	public:
		ushort m_LayerCount;
		ushort m_TriggerCount;
		AnimationDefArray* m_pAnimations;
		TransitionTable* m_pTransitions;
	};
}

namespace app
{
	class ResCharAnimScript : public fnd::ResCommon<animation::ResCharAnimScriptData>
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F60FC8));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	namespace animation
	{
		class ResCharAnim : public fnd::ResCommon<hh::gfx::res::ResAnimSkeleton>
		{
		public:
			ResCharAnim& operator =(hh::gfx::res::ResAnimSkeleton* pSkel)
			{
				m_pRes = pSkel;
				return *this;
			}
		};
	}
}