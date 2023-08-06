#pragma once

#include "runtime/window/windows/Window.h"
#include "runtime/rendering/RenderSurface.h"

#define NOMINMAX
#include <windows.h>

typedef struct GLFWwindow GLFWwindow;

namespace Rocket
{
	namespace Windows
	{
		class RkWin32Window : public RkWindow
		{
			RK_OBJECT_BODY()
		public:
			// Inherited via Window
			virtual bool Initialize(uint32 windowWidth, uint32 windowHeight, const rkstring& title) override;
			virtual void PreframeUpdate() override;
			virtual void PostFrameUpdate() override;
			virtual void Shutdown() override;
			virtual bool ShouldClose() const override;

			// return the native window handle.
			HWND GetHwnd();
		
		private:
			void MakeContextCurrent();

		private:
			GLFWwindow* m_GLFWWindow;
		};
	}
}
