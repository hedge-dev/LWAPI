#pragma once

namespace csl::fnd
{
	template<typename T>
	class Singleton
	{
	protected:
		static T** instance;

	public:
		[[nodiscard]] static T* GetInstance()
		{
			return *instance;
		}

		static void ReplaceInstance(T** inst)
		{
			if (*instance) delete *instance;
			instance = inst;
		}

		static bool IsInitialized()
		{
			return *instance != nullptr;
		}
	};
}