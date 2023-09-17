#pragma once

namespace app
{
	template <typename T>
	class EnemyState : public ut::StateBase<GameObject>
	{
	public:
		void Enter(GameObject& in_rObj, int in_unk) override { OnEnter(static_cast<T&>(in_rObj), in_unk); }
		void Leave(GameObject& in_rObj, int in_unk) override { OnLeave(static_cast<T&>(in_rObj), in_unk); }
		bool Update(GameObject& in_rObj, float in_deltaTime) override { return Step(static_cast<T&>(in_rObj), in_deltaTime); }

		virtual void OnEnter(T& in_rObj, int in_unk) {}

		virtual void OnLeave(T& in_rObj, int in_unk) {}

		virtual bool Step(T& in_rObj, float in_deltaTime) { return false; }

		void ChangeState(GameObject& in_rObj, int in_stateId)
		{
			in_rObj.GetComponent<GOCEnemyHsm>()->ChangeState(in_stateId);
		}
	};
}