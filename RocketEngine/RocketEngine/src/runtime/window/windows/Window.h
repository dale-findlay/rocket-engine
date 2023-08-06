#pragma once

#include "core/CoreMinimal.h"

namespace Rocket
{
	class RkWindow : RkObject
	{
		RK_OBJECT_BODY(RkObjectFlags::Abstract)
	public:
		virtual bool Initialize(uint32 windowWidth, uint32 windowHeight, const rkstring& title) = 0;
		virtual void PreframeUpdate() = 0;
		virtual void PostFrameUpdate() = 0;
		virtual void Shutdown() = 0;
		virtual bool ShouldClose() const = 0;
	};

}