#include "Win32Window.h"

#ifdef USE_D3D12
#include "runtime/rendering/dx12/DX12RenderSurface.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

bool Rocket::Windows::RkWin32Window::Initialize(uint32 windowWidth, uint32 windowHeight, const rkstring& title)
{
	if (!glfwInit())
		return false;

	m_GLFWWindow = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);

	if (!m_GLFWWindow)
	{
		glfwTerminate();
		return false;
	}

    return true;
}

void Rocket::Windows::RkWin32Window::Shutdown()
{
	glfwTerminate();
}

bool Rocket::Windows::RkWin32Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_GLFWWindow);
}

HWND Rocket::Windows::RkWin32Window::GetHwnd()
{
	return glfwGetWin32Window(m_GLFWWindow);
}

//TODO: move to GLRenderInterface
void Rocket::Windows::RkWin32Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(m_GLFWWindow);
}

void Rocket::Windows::RkWin32Window::PreframeUpdate()
{
	/*
		Dont need anything right now.
	*/
}

void Rocket::Windows::RkWin32Window::PostFrameUpdate()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(m_GLFWWindow);

	/* Poll for and process events */
	glfwPollEvents();
}
