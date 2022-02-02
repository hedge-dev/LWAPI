#pragma once

namespace app
{
	class CActivationManager;
	typedef uint EActivationOp;
	
	class CActivationHandle : public csl::ut::NonCopyable
	{
		friend CActivationManager;
	protected:
		CActivationManager* m_pOwner{};
		csl::math::Vector3 m_Position;
		INSERT_PADDING(8){};
		csl::ut::LinkListNode m_ListNode{ nullptr, nullptr };
		float m_Size;
		INSERT_PADDING(16){};
		
	public:
		virtual ~CActivationHandle();
		virtual void ActivationProc(EActivationOp op) = 0;
		virtual void SetAppearance(float opacity)
		{

		}
	};
}