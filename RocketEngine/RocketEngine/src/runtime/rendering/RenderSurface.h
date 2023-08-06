#pragma once
#include "core/CoreMinimal.h"

namespace Rocket
{
	class RkRenderSurface : public RkObject
	{
		RK_OBJECT_BODY(RkObjectFlags::Abstract)
	public:
		virtual bool Initialize() = 0;
	};
}
