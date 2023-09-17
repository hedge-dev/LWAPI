#pragma once

namespace app::game
{
	class GOCMovementComplex : public GOCMovement
	{
	private:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD7860));

	public:
		GOCMovementComplex() : GOCMovement()
		{
			
		}

		template <typename T>
		T* SetMoveController()
		{
			auto* pController = new T();
			if (!pController)
				return { nullptr };

			SetupController(pController);

			return pController;
		}

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
	};
}