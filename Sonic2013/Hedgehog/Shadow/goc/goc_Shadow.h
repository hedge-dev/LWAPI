#pragma once

namespace app::game
{
	class ShadowShape;

	class GOCShadow : public fnd::GOComponent
	{
	public:
		class Description
		{
		public:
			int ShadowCount;
			
			Description(int in_shadowCount) : ShadowCount(in_shadowCount)
			{
				
			}
		};
		
	private:
		inline static FUNCTION_PTR(ShadowShape*, __thiscall, ms_fpSetup, ASLR(0x004CBAE0), GOCShadow*, const Description&);
		inline static FUNCTION_PTR(ShadowShape*, __thiscall, ms_fpCreateShape, ASLR(0x004CBB60), GOCShadow*, const ShadowShapeCInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetVisible, ASLR(0x004CB9E0), GOCShadow*, bool);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD78D0));

	public:
		csl::ut::ObjectMoveArray<ShadowShape> ShadowShapes{ m_pAllocator };
		int Unk1{};

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
		
		void Setup(const Description& in_rDescription)
		{
			ms_fpSetup(this, in_rDescription);
		}

		ShadowShape* CreateShape(const ShadowShapeCInfo& in_rCreateInfo)
		{
			return ms_fpCreateShape(this, in_rCreateInfo);
		}

		void SetVisible(bool in_isVisible)
		{
			ms_fpSetVisible(this, in_isVisible);
		}
	};
}