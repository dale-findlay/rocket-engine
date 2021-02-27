#pragma once

#include "runtime/window/windows/Window.h"
#include <glfw/glfw3.h>

namespace Rocket
{
	namespace Windows
	{
		class Win32Window : public Window
		{
		public:
			// Inherited via Window
			virtual bool Initialize(uint32 windowWidth, uint32 windowHeight, const rkstring& title) override;
			virtual void PreframeUpdate() override;
			virtual void PostFrameUpdate() override;
			virtual void Shutdown() override;
			virtual bool ShouldClose() const override;
			virtual void MakeContextCurrent() override;

		private:
			GLFWwindow* m_WindowHandle;

		};
	}
}
