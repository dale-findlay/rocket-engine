#pragma once

#include "core/CoreTypes.h"
#include "core/CoreMacros.h"
#include <uuid.h>

namespace Rocket
{
	class UniqueId
	{
	public:
		UniqueId();

		FORCEINLINE rkstring GetAsString() const
		{
			return uuids::to_string(m_uid);
		}

	private:
		uuids::uuid	m_uid;
	};
}