#include "RendererManager.h"

#include "runtime/Engine.h"
#include "runtime/memory/MemoryManager.h"

#include "runtime/renderering/renderers/ForwardRenderer.h"

Rocket::RendererManager::RendererManager()
    : EngineSubsystem(), m_MemoryAllocator(nullptr)
{}

bool Rocket::RendererManager::Init()
{
    MemoryAllocatorCreateInfo createInfo = {};
    createInfo.maxSize = 4 * 1024 * 1024;
    createInfo.name = "Renderer";
    createInfo.type = MemoryAllocatorType::FreeList;

    m_MemoryAllocator = gEngine->GetMemoryManager()->CreateMemoryAllocator(createInfo);

    m_Renderer = new Rendering::ForwardRenderer();
    m_Renderer->Init();

    return true;
}

void Rocket::RendererManager::Shutdown()
{
    if (m_Renderer != nullptr)
    {
        m_Renderer->Shutdown();
        delete m_Renderer;
        m_Renderer = nullptr;
    } 
}

void Rocket::RendererManager::DrawFrame()
{
    m_Renderer->DrawFrame();
}

Rocket::Renderer* Rocket::RendererManager::GetRenderer()
{
    return m_Renderer;
}
