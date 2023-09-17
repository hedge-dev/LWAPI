#pragma once

namespace app
{
	class EnemyUvAnimLinkController
	{
	public:
		typedef size_t MotionMirrorType;
		
		struct UVAnimLinkInfo
		{
			csl::ut::ObjectMoveArray<hh::gfx::res::ResAnimTexSrt> Animations{};
			INSERT_PADDING(68);
		};

		class Description
		{
		public:
			size_t AnimationLinkCount{};
			size_t UvAnimationCount{};
			float Unk3{};
			GameObjectHandle<GameObject> Owner{};
			csl::ut::Bitset<byte> Unk4{};
		};

		int Unk1{};
		csl::ut::ObjectMoveArray<UVAnimLinkInfo> LinkInfos{};
		csl::ut::ObjectMoveArray<hh::gfx::res::ResAnimTexSrt> Animations{};
		GameObjectHandle<GameObject> Owner{ nullptr };

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpChangeCallback, ASLR(0x0072D4D0), EnemyUvAnimLinkController*, animation::CharactorAnimation*, animation::ETriggerValueType, animation::CallbackParam);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x0072D780), EnemyUvAnimLinkController*, Description, csl::fnd::IAllocator*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpAdd, ASLR(0x0072D2A0), EnemyUvAnimLinkController*, hh::gfx::res::ResAnimTexSrt, const char*, MotionMirrorType);

	public:
		void ChangeCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			ms_fpChangeCallback(this, in_pAnimation, in_triggerType, in_param);
		}

		bool Setup(Description in_description, csl::fnd::IAllocator* in_pAllocator)
		{
			return ms_fpSetup(this, in_description, in_pAllocator);
		}

		bool Add(hh::gfx::res::ResAnimTexSrt in_pUvAnimation, const char* in_pAnimName, MotionMirrorType in_mirrorType)
		{
			return ms_fpAdd(this, in_pUvAnimation, in_pAnimName, in_mirrorType);
		}
	};
}