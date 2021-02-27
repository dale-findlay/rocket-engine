#include "WindowManager.h"

#include "runtime/window/windows/Window.h"
#include "runtime/window/windows/Win32Window.h"

Rocket::WindowManager::WindowManager()
	: EngineSubsystem(), m_window(nullptr)
{}

bool Rocket::WindowManager::Init()
{
	m_window = new Windows::Win32Window();
	m_window->Initialize(1366, 768, "rocketEngine");

	SetIsInitialized(true);

	return true;
}

void Rocket::WindowManager::Shutdown()
{
	if (m_window != nullptr)
	{
		m_window->Shutdown();
		delete m_window;
	}

	SetIsInitialized(false);
	SetIsShutdown(true);
}

void Rocket::WindowManager::PreFrameUpdate()
{
	m_window->PreframeUpdate();
}

void Rocket::WindowManager::PostFrameUpdate()
{
	m_window->PostFrameUpdate();
}