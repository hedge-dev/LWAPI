#pragma once

namespace app
{
	class AnimalManager
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateAnimal, ASLR(0x00727EA0), GameDocument&, const csl::math::Matrix34&, const csl::math::Vector3&);

		INSERT_PADDING(1024);

	public:
		void CreateAnimal(GameDocument& in_rDocument, const csl::math::Matrix34& in_rMtx, const csl::math::Vector3& in_rVec)
		{
			ms_fpCreateAnimal(in_rDocument, in_rMtx, in_rVec);
		}
	};
}