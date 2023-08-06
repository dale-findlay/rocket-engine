#include "ObjectManager.h"
#include "runtime/memory/MemoryManager.h"

Rocket::ObjectManager* Rocket::gObjectManager = nullptr;

bool Rocket::ObjectManager::Init()
{
	//MemoryAllocatorCreateInfo gen1CreateInfo = {};
	//gen1CreateInfo.maxSize = 4 * 1024 * 1024;
	//gen1CreateInfo.name = "ObjectManager_Gen1";
	//gen1CreateInfo.type = MemoryAllocatorType::FreeList;
	//m_Gen1Allocator = gMemoryManager->CreateMemoryAllocator(gen1CreateInfo);

	return true;
}

void Rocket::ObjectManager::Shutdown()
{
	for (const auto& object : m_Objects)
	{
		object->Destroy();
	}

	//TODO: Make this a bit safer!
	Tick(); // manually tick the GC to make sure the objects get cleaned up.
}

void Rocket::ObjectManager::Tick()
{
	// loop through all the objects that are unreachable and properly clean them up.
	for (const auto& object : m_Objects)
	{
		if (object->IsPendingCleanup())
		{

		}
	}
}
