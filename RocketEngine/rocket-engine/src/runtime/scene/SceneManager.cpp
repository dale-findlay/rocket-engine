#include "SceneManager.h"

#include "runtime/Engine.h"

Rocket::SceneManager::SceneManager()
    : EngineSubsystem(), m_EntityFactory(nullptr), m_Allocator(nullptr)
{}

bool Rocket::SceneManager::Init()
{
	MemoryAllocatorCreateInfo createInfo = {};
	createInfo.maxSize = 10 * 1024 * 1024; //10 MB - probably needs more maybe idk haha!?
	createInfo.name = "SceneManager";
	createInfo.type = MemoryAllocatorType::FreeList;

    m_Allocator = gEngine->GetMemoryManager()->CreateMemoryAllocator(createInfo);

	m_EntityFactory = new Rocket::EntityFactory();
	
	SetIsInitialized(true);
    return true;
}

void Rocket::SceneManager::Shutdown()
{	
	if (m_EntityFactory != nullptr)
	{
		m_EntityFactory->RecycleAllEntities();
		delete m_EntityFactory;
		m_EntityFactory = nullptr;
	}

	SetIsInitialized(false);
	SetIsShutdown(true);
}
