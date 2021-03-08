#include "Factory.h"

#include "runtime/Engine.h"

Rocket::Memory::MemoryAllocator* Rocket::FactoryUtils::CreateMemoryAllocator(size_t size)
{
	UniqueId id;

	MemoryAllocatorCreateInfo createInfo = {};
	createInfo.maxSize = size; 
	createInfo.name = "SceneManager";
	createInfo.type = MemoryAllocatorType::FreeList;

	return gEngine->GetMemoryManager()->CreateMemoryAllocator(createInfo);
}
