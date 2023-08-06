#pragma once

#include "runtime/rendering/Renderer.h"

namespace Rocket
{
	namespace Rendering
	{
		class ForwardRenderer : public Renderer
		{
		public:
			ForwardRenderer();

			// Inherited via Renderer
			virtual bool Init() override;
			virtual void Shutdown() override;
			virtual void DrawFrame() override;
		};
	}
}