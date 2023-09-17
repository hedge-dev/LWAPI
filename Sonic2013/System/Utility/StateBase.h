#pragma once

namespace app::ut::internal
{
	class HsmEvent
	{
	public:
		union
		{
			int Int;
			float Float;
			fnd::Message* pMessage{};
		};
	};

	class StateImpl : public fnd::ReferencedObject
	{
	public:
		INSERT_PADDING(8);

		virtual bool Trigger(void* in_pObj, int in_state, internal::HsmEvent& in_rEvent) = 0;
	};

	typedef StateImpl* (*StateCreate_t)(csl::fnd::IAllocator*);

	class StateDescImpl
	{
	public:
		const char* pName{};
		StateCreate_t fpCreate{};
		int Unk1{};
	};
}

namespace app::ut
{
	template <typename T>
	class StateBase : public internal::StateImpl
	{
	public:
		bool Trigger(void* in_pObj, int in_state, internal::HsmEvent& in_rEvent) override
		{
			switch (in_state)
			{
			case 1:
			{
				return Init(*static_cast<T*>(in_pObj));
			}
			case 2:
			{
				Enter(*static_cast<T*>(in_pObj), in_rEvent.Int);
				return true;
			}
			case 3:
			{
				Leave(*static_cast<T*>(in_pObj), in_rEvent.Int);
				return true;
			}
			case 4:
			{
				return Update(*static_cast<T*>(in_pObj), in_rEvent.Float);
			}
			case 5:
			{
				return ProcessMessage(*static_cast<T*>(in_pObj), *in_rEvent.pMessage);
			}
			default:
				return 0;
			}
		}

		virtual bool Init(T& in_rObj) { return false; }
		virtual void Enter(T& in_rObj, int in_unk) {}
		virtual void Leave(T& in_rObj, int in_unk) {}
		virtual bool Update(T& in_rObj, float in_deltaTime) { return false; }
		virtual bool ProcessMessage(T& in_rObj, fnd::Message& in_rMessage) { return false; }
	};

	template <typename T>
	class StateCreatorFuncTemplate
	{
	public:
		inline static StateBase<typename T::context_type>* Create(csl::fnd::IAllocator* in_pAllocator)
		{
			return reinterpret_cast<StateBase<typename T::context_type>*>(new(in_pAllocator) T());
		}
	};
}