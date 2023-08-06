#pragma once
#include "RenderSurface.h"

namespace Rocket
{
	class RenderInterface
	{
	public:
		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual RkRenderSurface* ConstructRenderSurface() = 0;
	};
}