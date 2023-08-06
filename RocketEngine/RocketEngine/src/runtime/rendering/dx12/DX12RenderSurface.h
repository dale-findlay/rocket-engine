#pragma once
#include "core/CoreMinimal.h"
#include "../RenderSurface.h"

namespace Rocket
{
	class RkDX12RenderSurface : public RkRenderSurface
	{
		RK_OBJECT_BODY()
	public:

		virtual bool Initialize() override;

	private:

	};
}