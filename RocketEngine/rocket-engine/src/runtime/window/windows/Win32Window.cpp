#include "Win32Window.h"

bool Rocket::Windows::Win32Window::Initialize(uint32 windowWidth, uint32 windowHeight, const rkstring& title)
{
	if (!glfwInit())
		return false;

	m_WindowHandle = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);

	if (!m_WindowHandle)
	{
		glfwTerminate();
		return false;
	}

    return true;
}

void Rocket::Windows::Win32Window::Shutdown()
{
	glfwTerminate();
}

bool Rocket::Windows::Win32Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_WindowHandle);
}

void Rocket::Windows::Win32Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(m_WindowHandle);
}

void Rocket::Windows::Win32Window::PreframeUpdate()
{
	/*
		Dont need anything right now.
	*/
}

void Rocket::Windows::Win32Window::PostFrameUpdate()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(m_WindowHandle);

	/* Poll for and process events */
	glfwPollEvents();
}
