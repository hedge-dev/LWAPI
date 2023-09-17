#pragma once

namespace app::game
{
	class GOCShadowSimple : public GOCShadow
	{
	public:
		class Description
		{
		public:
			ShadowShapeCInfo* pCreateInfo;

			Description(ShadowShapeCInfo* in_pCreateInfo) : pCreateInfo(in_pCreateInfo)
			{
				
			}
		};

		ShadowShape* pShadowShape{};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalOffsetPosition, ASLR(0x004CBEB0), GOCShadowSimple*, const csl::math::Vector3&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetMaxDownDist, ASLR(0x004CBE70), GOCShadowSimple*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetVisible, ASLR(0x004CBE50), GOCShadowSimple*, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetScale, ASLR(0x004CBE90), GOCShadowSimple*, const csl::math::Vector3&);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD78EC));

	public:
		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& in_rDescription)
		{
			if (!in_rDescription.pCreateInfo)
				return;

			GOCShadow::Setup({ 1 });
			ShadowShape* pShape = CreateShape(*in_rDescription.pCreateInfo);
			if (!pShape)
				return;
			
			pShape->SetUserID(0);
			pShadowShape = pShape;
		}

		void SetLocalOffsetPosition(const csl::math::Vector3& in_rPosition)
		{
			ms_fpSetLocalOffsetPosition(this, in_rPosition);
		}

		void SetVisible(bool in_isVisible)
		{
			ms_fpSetVisible(this, in_isVisible);
		}

		void SetScale(const csl::math::Vector3& in_rScale)
		{
			ms_fpSetScale(this, in_rScale);
		}

		void SetMaxDownDist(float in_maxDownDist)
		{
			ms_fpSetMaxDownDist(this, in_maxDownDist);
		}
	};
}