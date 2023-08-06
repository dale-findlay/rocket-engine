#include "Engine.h"

Rocket::Engine* Rocket::gEngine = nullptr;

bool Rocket::Engine::Init()
{
    ResetRuntimeExecutionFlags();
    
    RK_ASSERT(gEngine == nullptr);
    gEngine = this;

	// Initialize the core engine subsystems, these are outside of the rk-object ecosystem.
	RK_ASSERT(gMemoryManager == nullptr && gObjectManager == nullptr);
	gMemoryManager = new MemoryManager();
	gObjectManager = new ObjectManager();

    if (!InitEngineSubsystems())
    {
        ShutdownEngineSubsystems();
        return false;
    }

    return true;
}

void Rocket::Engine::ResetRuntimeExecutionFlags()
{
    bShouldClose = false;
    bInitializationError = false;
}

int32 Rocket::Engine::Run()
{
    RkRendererManager* renderingManager = GetSubsystem<Rocket::RkRendererManager>();
    RkWindowManager* windowManager = GetSubsystem<Rocket::RkWindowManager>();

    while (!bShouldClose)
    {
        windowManager->PreFrameUpdate();
        renderingManager->DrawFrame();
        windowManager->PostFrameUpdate();

        bShouldClose = windowManager->GetWindow()->ShouldClose();
    }

    return 0;
}

void Rocket::Engine::Shutdown()
{
    ShutdownEngineSubsystems();

	// kill the core engine subsystems
	delete gObjectManager;
	gObjectManager = nullptr;

	delete gMemoryManager;
	gMemoryManager = nullptr;
}

bool Rocket::Engine::InitEngineSubsystems()
{
    // Initialize none-core engine subsystems - these are now rk objects.
    RegisterSubsystem<Rocket::RkWindowManager>();
    RegisterSubsystem<Rocket::RkRendererManager>();
    //RegisterSubsystem<Rocket::SceneManager>();
	
    return true;
}

void Rocket::Engine::ShutdownEngineSubsystems()
{
	UnregisterSubsystem<Rocket::RkRendererManager>();
	UnregisterSubsystem<Rocket::RkWindowManager>();
}
