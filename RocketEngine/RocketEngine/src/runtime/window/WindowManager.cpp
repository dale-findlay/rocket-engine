#include "WindowManager.h"

#include "runtime/window/windows/Window.h"
#include "runtime/window/windows/Win32Window.h"

Rocket::RkWindowManager::RkWindowManager()
	: RkEngineSubsystem(), m_window(nullptr)
{}

bool Rocket::RkWindowManager::Init()
{
	m_window = new Windows::RkWin32Window();
	m_window->Initialize(1366, 768, "rocketEngine");

	SetIsInitialized(true);

	return true;
}

void Rocket::RkWindowManager::Shutdown()
{
	if (m_window != nullptr)
	{
		m_window->Shutdown();
		delete m_window;
	}

	SetIsInitialized(false);
	SetIsShutdown(true);
}

void Rocket::RkWindowManager::PreFrameUpdate()
{
	m_window->PreframeUpdate();
}

void Rocket::RkWindowManager::PostFrameUpdate()
{
	m_window->PostFrameUpdate();
}