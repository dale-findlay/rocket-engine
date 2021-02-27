#pragma once

namespace Rocket
{
	namespace Rendering
	{
		class RenderCommand
		{
		public:
			virtual void Execute() = 0;
		};
	}
}