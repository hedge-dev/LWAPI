#pragma once
#define TiFSM_SIGNAL_SUPER -1
#define TiFSM_SIGNAL_INIT -2
#define TiFSM_SIGNAL_ENTER -3
#define TiFSM_SIGNAL_LEAVE -4
#define TiFSM_SIGNAL_UPDATE 0
#define TiFSM_SIGNAL_MESSAGE 1
#define TiFSM_SIGNAL_USER 100

#define TiFSM_OPTION_USE_FP_TOP 0

namespace app
{
	inline static void* fpFsmTop = reinterpret_cast<void*>(ASLR(0x007B7030));
	
	template<const int Option>
	class TinyFsmSetOption;

	template<typename T, typename TEvent>
	class TTinyFsmState;

	template<typename T, typename TEvent>
	class TTinyFsmEvent;

	template<typename T>
	class TiFsmBasicEvent;

	template<typename T, typename TEvent = TiFsmBasicEvent<T>, const bool Hierarchical = false>
	class TTinyFsm
	{
	private:
		typedef TTinyFsmState<T, TEvent> State_t;

	public:
		typedef TEvent TiFsmEvent_t;
		typedef State_t TiFsmState_t;
		typedef TiFsmState_t(*TiFsmHookState_t)(T& in_self, const TEvent& in_event);

	private:
		State_t m_Src;
		State_t m_Cur;

		State_t _top(const TEvent& e) { return {}; }

		template<TiFsmHookState_t HookFunc>
		State_t _hook(const TEvent& e) { return HookFunc(*static_cast<T*>(this), e); }

		State_t Trigger(const State_t& in_state, const TEvent& in_event)
		{
			return in_state(static_cast<T*>(this), in_event);
		}

		State_t Super(const State_t& in_state)
		{
			return Trigger(in_state, { TiFSM_SIGNAL_SUPER });
		}

		State_t Init(const State_t& in_state)
		{
			return Trigger(in_state, { TiFSM_SIGNAL_INIT });
		}

		State_t Enter(const State_t& in_state)
		{
			return Trigger(in_state, { TiFSM_SIGNAL_ENTER });
		}

		State_t Leave(const State_t& in_state)
		{
			return Trigger(in_state, { TiFSM_SIGNAL_LEAVE });
		}

		void InitCurrentState()
		{
			while (Init(m_Cur) == nullptr)
			{
				Enter(m_Cur);
			}
		}

	public:
		inline static State_t FSM_TOP()
		{
			if constexpr (std::is_base_of<TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>, T>())
			{
				return csl::ut::union_cast<State_t>(fpFsmTop);
			}
			else
				return { &TTinyFsm::_top };
		}

		template<TiFsmHookState_t HookFunc>
		inline static State_t FSM_HOOK()
		{
			return { &TTinyFsm::_hook<HookFunc> };
		}

		void FSM_INIT(State_t in_state)
		{
			m_Cur = in_state;
		}

		void FSM_TRAN(State_t in_state)
		{
			if constexpr (Hierarchical)
			{
				for (State_t state = m_Cur; state != m_Src; state = Super(state))
				{
					Leave(state);
				}

				if (m_Src == in_state)
				{
					Leave(m_Src);
					Enter(in_state);
				}
				else
				{
					csl::ut::InplaceMoveArray<State_t, 5> oldStates{ fnd::GetTempAllocator() };
					csl::ut::InplaceMoveArray<State_t, 5> newStates{ fnd::GetTempAllocator() };
					State_t oldState = m_Cur;
					State_t newState = in_state;

					while (oldState != FSM_TOP())
					{
						oldStates.push_back(oldState);
						oldState = Super(oldState);
					}

					while (newState != FSM_TOP())
					{
						newStates.push_back(newState);
						newState = Super(newState);
					}

					// I honestly don't even know what this is supposed to do
					std::reverse(oldStates.begin(), oldStates.end());
					std::reverse(newStates.begin(), newStates.end());

					auto* enumerator = oldStates.begin();
					auto* enumerator2 = newStates.begin();

					while(*enumerator != oldStates[0] && *enumerator2 != newStates[0] && *enumerator == *enumerator2)
					{
						++enumerator;
						++enumerator2;
					}

					State_t oldUniqueState = *enumerator;
					std::reverse(oldStates.begin(), oldStates.end());

					for (auto& state : oldStates)
					{
						Leave(state);
						if (state == oldUniqueState)
							break;
					}

					while(*enumerator2 != newStates[0])
					{
						Enter(*enumerator2);
						++enumerator2;
					}
				}

				m_Cur = in_state;
				InitCurrentState();
			}
			else
			{
				Leave(m_Cur);
				m_Cur = in_state;
				Enter(m_Cur);
			}
		}

		void FSM_SET_INITSTATE(State_t in_state)
		{
			m_Cur = in_state;
		}

		void FSM_SETSTATE(State_t in_state)
		{
			m_Src = m_Cur;
			FSM_TRAN(in_state);
		}

		State_t FSM_STATE() const
		{
			return m_Cur;
		}

		void InitFSM()
		{
			if constexpr (Hierarchical)
			{
				csl::ut::InplaceMoveArray<State_t, 5> stateStack{ fnd::GetTempAllocator() };
				State_t fsmState = m_Cur;

				while (fsmState != FSM_TOP())
				{
					stateStack.push_back(fsmState);
					fsmState = Super(fsmState);
				}

				std::reverse(stateStack.begin(), stateStack.end());
				for (auto& state : stateStack)
				{
					Enter(state);
				}

				InitCurrentState();
			}
			else
			{
				Enter(m_Cur);
			}
		}

		void ShutdownFSM()
		{
			if constexpr (Hierarchical)
			{
				State_t state = m_Cur;
				while (state != FSM_TOP())
				{
					Leave(state);
					state = Super(state);
				}

				m_Cur.Clear();
				m_Src.Clear();
			}
			else
			{
				Leave(m_Cur);
				m_Cur.Clear();
			}
		}

		void DispatchFSM(const TEvent& in_event)
		{
			if constexpr (Hierarchical)
			{
				m_Src = m_Cur;

				while (m_Src)
				{
					State_t state = Trigger(m_Src, in_event);
					if (!state) break;

					m_Src = Super(m_Src);
				}
			}
			else
			{
				Trigger(m_Cur, in_event);
			}
		}

		TTinyFsm() : m_Src(FSM_TOP()), m_Cur(nullptr) {}
		TTinyFsm(State_t in_src) : m_Src(FSM_TOP()), m_Cur(in_src)
		{
			
		}

		virtual ~TTinyFsm() = default;
	};

	template<typename T, typename TEvent>
	class TTinyFsmState
	{
	public:
		typedef TTinyFsmState(T::*Delegate_t)(const TEvent& e);
		Delegate_t m_Delegate{};

		TTinyFsmState() = default;
		TTinyFsmState(Delegate_t in_func) : m_Delegate(in_func) {}

		[[nodiscard]] bool IsValid() const
		{
			return m_Delegate != nullptr;
		}

		void Clear()
		{
			m_Delegate = nullptr;
		}

		TTinyFsmState Call(T* in_pObj, const TEvent& e) const
		{
			if (IsValid())
				return (in_pObj->*m_Delegate)(e);

			return {};
		}

		operator bool() const
		{
			return IsValid();
		}

		operator Delegate_t() const
		{
			return m_Delegate;
		}

		bool operator==(const TTinyFsmState& in_other) const
		{
			return m_Delegate == in_other.m_Delegate;
		}

		bool operator!=(const TTinyFsmState& in_other)
		{
			return m_Delegate != in_other.m_Delegate;
		}

		bool operator==(const Delegate_t& in_other) const
		{
			return m_Delegate == in_other;
		}

		bool operator!=(const Delegate_t& in_other) const
		{
			return m_Delegate != in_other;
		}

		TTinyFsmState operator()(T* in_pObj, const TEvent& e) const
		{
			return Call(in_pObj, e);
		}
	};

	template<typename T, typename TEvent>
	class TTinyFsmEvent
	{
	public:
		int m_Sig{};

		TTinyFsmEvent(int in_sig) : m_Sig(in_sig)
		{
			
		}

		int getSignal() const
		{
			return m_Sig;
		}
	};

	template<typename T>
	class TiFsmBasicEvent : public TTinyFsmEvent<T, TiFsmBasicEvent<T>>
	{
	public:
		union
		{
			int m_Int;
			float m_Float;
			fnd::Message* m_pMessage{};
		};

		TiFsmBasicEvent(int in_sig) : TTinyFsmEvent<T, TiFsmBasicEvent>(in_sig) {  }
		TiFsmBasicEvent(int in_sig, float in_float) : TTinyFsmEvent<T, TiFsmBasicEvent>(in_sig)
		{
			m_Float = in_float;
		}

		TiFsmBasicEvent(int in_sig, int in_int) : TTinyFsmEvent<T, TiFsmBasicEvent>(in_sig)
		{
			m_Int = in_int;
		}

		TiFsmBasicEvent(int in_sig, fnd::Message& in_msg) : TTinyFsmEvent<T, TiFsmBasicEvent>(in_sig)
		{
			m_pMessage = &in_msg;
		}

		[[nodiscard]] float getFloat() const { return m_Float; }
		[[nodiscard]] int getInt() const { return m_Int; }
		[[nodiscard]] fnd::Message& getMessage() const { return *m_pMessage; }

		inline static TiFsmBasicEvent CreateUpdate(float in_deltaTime)
		{
			return { TiFSM_SIGNAL_UPDATE, in_deltaTime };
		}

		inline static TiFsmBasicEvent CreateMessage(fnd::Message& in_msg)
		{
			return { TiFSM_SIGNAL_MESSAGE, in_msg };
		}
	};

	template<const int Option>
	class TinyFsmSetOption
	{
		
	};
}