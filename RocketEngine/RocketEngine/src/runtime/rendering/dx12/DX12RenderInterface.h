#pragma once
#include "../RenderInterface.h"

namespace Rocket
{
	class DX12RenderInterface : public Rocket::RenderInterface
	{
		// Inherited via RenderInterface
		virtual bool Initialize() override;
		virtual void Shutdown() override;
		virtual RkRenderSurface* ConstructRenderSurface() override;
	};
}
