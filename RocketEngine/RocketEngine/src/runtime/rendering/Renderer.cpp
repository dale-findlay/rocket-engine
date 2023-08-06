#include "Renderer.h"
#include "runtime/Engine.h"
#include "runtime/rendering/RendererManager.h"

Rocket::Renderer::Renderer()
	: m_CommandPoolAllocator(nullptr), frameIndex(1)
{}

bool Rocket::Renderer::Init()
{
	m_RenderManager = gEngine->GetSubsystem<RkRendererManager>();

	const size_t renderCommandPoolSize = 1024 * 1024; //1MB

	void* pMemory = m_RenderManager->GetMemoryAllocator()->Allocate(renderCommandPoolSize);
	m_CommandPoolAllocator = new Memory::LinearAllocator(renderCommandPoolSize, pMemory);

	return true;
}

void Rocket::Renderer::Shutdown()
{
	if (m_CommandPoolAllocator != nullptr)
	{
		void* ptr = m_CommandPoolAllocator->GetStart();
		m_RenderManager->GetMemoryAllocator()->Deallocate(ptr);
	}

	delete m_CommandPoolAllocator;
	m_CommandPoolAllocator = nullptr;
}

void Rocket::Renderer::DrawFrame()
{
	for (auto& it : m_CurrentFrameCommands)
	{
		it->Execute();
	}

	frameIndex++;
	ClearRenderCommands();
}

void Rocket::Renderer::ClearRenderCommands()
{
	m_CurrentFrameCommands.clear();

	if (m_CommandPoolAllocator != nullptr)
	{
		m_CommandPoolAllocator->Clear();
	}
}