#include "Engine.h"

bool Rocket::Engine::Init()
{
    ResetRuntimeExecutionFlags();

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
}

void Rocket::Engine::UpdatePostRenderSystems()
{
}

int32 Rocket::Engine::Run()
{
    while (!bShouldClose)
    {
        UpdatePreRenderSystems();
        
        //m_Renderer->Update();
        //m_Renderer->DrawFrame();

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

    return true;
}

void Rocket::Engine::ShutdownEngineSystems()
{
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
