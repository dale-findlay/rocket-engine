#include "ResourceManager.h"

#include "runtime/Engine.h"

Rocket::ResourceManager::ResourceManager()
{
}

bool Rocket::ResourceManager::Init()
{
	MemoryAllocatorCreateInfo createInfo = {};
	createInfo.maxSize = 4 * 1024 * 1024;
	createInfo.name = "Resource Manager";
	createInfo.type = MemoryAllocatorType::FreeList;

	m_Allocator = gEngine->GetMemoryManager()->CreateMemoryAllocator(createInfo);
		
    return true;
}

void Rocket::ResourceManager::Shutdown()
{
}
