#pragma once

namespace app::Player
{
	namespace internal
	{
		class PluginImpl : public fnd::ReferencedObject
		{
		public:
			inline static constexpr int FLAG_IS_STATUS_END = 0;

			const char* pName{};
			int Index{ -1 };
			csl::ut::Bitset<uint> Flags{};

			PluginImpl(const char* in_pName)
			{
				pName = in_pName;
			}

			bool IsStatusEnd() const
			{
				return Flags.test(FLAG_IS_STATUS_END);
			}

			void SetIndex(int in_index)
			{
				Index = in_index;
			}

			void SetStatusEnd()
			{
				Flags.set(FLAG_IS_STATUS_END, true);
			}
		};
	}

	template <typename T>
	class PluginBase : public internal::PluginImpl
	{
	public:
		PluginBase<T>(const char* in_pName) : internal::PluginImpl(in_pName)
		{

		}

		virtual void OnEnter(T& in_rObject);
		virtual void OnLeave(T& in_rObject);
		virtual bool Update(T& in_rObject, float in_deltaTime) { return true; }
		virtual bool ProcessMessage(T& in_rObject, fnd::Message& in_rMessage) { return false; }
	};
}