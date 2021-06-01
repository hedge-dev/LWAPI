#pragma once

namespace app
{
	typedef uint EActivationOp;
	
	class CActivationHandle : csl::ut::NonCopyable
	{
	protected:
		csl::math::Vector3 m_Position;
		INSERT_PADDING(16);
		float m_Size;
		INSERT_PADDING(16);
		
	public:
		virtual ~CActivationHandle() = default;
		virtual void ActivationProc(EActivationOp op) = 0;
		virtual void SetAppearance(float opacity)
		{
			
		}
	};
}