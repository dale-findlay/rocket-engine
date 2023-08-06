#include "RendererManager.h"

#include "runtime/Engine.h"
#include "runtime/memory/MemoryManager.h"

#include "runtime/rendering/renderers/ForwardRenderer.h"

Rocket::RkRendererManager::RkRendererManager()
    : RkEngineSubsystem(), m_MemoryAllocator(nullptr)
{}

bool Rocket::RkRendererManager::Init()
{
    MemoryAllocatorCreateInfo createInfo = {};
    createInfo.maxSize = 4 * 1024 * 1024;
    createInfo.name = "Renderer";
    createInfo.type = MemoryAllocatorType::FreeList;

    m_MemoryAllocator = gMemoryManager->CreateMemoryAllocator(createInfo);

    m_Renderer = new Rendering::ForwardRenderer();
    m_Renderer->Init();

    return true;
}

void Rocket::RkRendererManager::Shutdown()
{
    if (m_Renderer != nullptr)
    {
        m_Renderer->Shutdown();
        delete m_Renderer;
        m_Renderer = nullptr;
    } 
}

void Rocket::RkRendererManager::DrawFrame()
{
    m_Renderer->DrawFrame();
}

Rocket::Renderer* Rocket::RkRendererManager::GetRenderer()
{
    return m_Renderer;
}
