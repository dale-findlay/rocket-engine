#include "Engine.h"

Rocket::Engine* Rocket::gEngine = nullptr;

bool Rocket::Engine::Init()
{
    ResetRuntimeExecutionFlags();
    
    ROCKETASSERT(gEngine == nullptr);
    gEngine = this;

    if (!InitEngineSystems())
    {
        ShutdownEngineSystems();
        return false;
    }

    return true;
}

void Rocket::Engine::ResetRuntimeExecutionFlags()
{
    bShouldClose = false;
    bInitializationError = false;
}

void Rocket::Engine::UpdatePreRenderSystems()
{    
    m_WindowManager->PreFrameUpdate();
}

void Rocket::Engine::UpdatePostRenderSystems()
{
    m_WindowManager->PostFrameUpdate();
    bShouldClose = m_WindowManager->GetWindow()->ShouldClose();
}

int32 Rocket::Engine::Run()
{
    while (!bShouldClose)
    {
        UpdatePreRenderSystems();
        
        m_RendererManager->DrawFrame();

        UpdatePostRenderSystems();
    }

    return 0;
}

void Rocket::Engine::Shutdown()
{
    ShutdownGameSystems();
    ShutdownEngineSystems();
}

bool Rocket::Engine::InitEngineSystems()
{
    m_MemoryManager = new Rocket::MemoryManager();
    if (!m_MemoryManager->Init())
    {
        m_MemoryManager->Shutdown();
        return false;
    }

	m_WindowManager = new Rocket::WindowManager();
	if (!m_WindowManager->Init())
	{
        m_WindowManager->Shutdown();
		return false;
	}

    m_RendererManager = new Rocket::RendererManager();
    if (!m_RendererManager->Init())
    {
        m_RendererManager->Shutdown();
		return false;
    }

    return true;
}

void Rocket::Engine::ShutdownEngineSystems()
{
	if (m_RendererManager != nullptr)
	{
		m_RendererManager->Shutdown();
		delete m_RendererManager;
		m_RendererManager = nullptr;
	}

	if (m_WindowManager != nullptr)
	{
        m_WindowManager->Shutdown();
		delete m_WindowManager;
        m_WindowManager = nullptr;
	}

    if (m_MemoryManager != nullptr)
    {
        m_MemoryManager->Shutdown();
        delete m_MemoryManager;
        m_MemoryManager = nullptr;
    }
}

bool Rocket::Engine::InitGameSystems()
{
    return true;
}

void Rocket::Engine::ShutdownGameSystems()
{
}
