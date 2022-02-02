#include "ActivationHandle.h"
#pragma once

namespace app
{
	inline CActivationHandle::~CActivationHandle()
	{
		ASSERT_OFFSETOF(CActivationHandle, m_pOwner, 16);

		if (m_pOwner)
			m_pOwner->RemoveObject(this);
	}
}