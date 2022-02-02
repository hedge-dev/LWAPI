#include "MyActivationHandle.h"
#pragma once

namespace app
{
	inline void CMyActivationHandle::ActivationProc(EActivationOp op)
	{
		if (m_pOwner)
			m_pOwner->Deactivate();
	}
}