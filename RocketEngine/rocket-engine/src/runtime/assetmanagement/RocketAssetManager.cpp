#include "RocketAssetManager.h"

#include "runtime/Engine.h"
#include "runtime/assetmanagement/Asset.h"

bool Rocket::RocketAssetManager::Init()
{
    //Create subsystem's memory allocator.
	MemoryAllocatorCreateInfo createInfo = {};
	createInfo.maxSize = 1 * 1024 * 1024; //1MB
	createInfo.name = "RocketAssetManager";
	createInfo.type = MemoryAllocatorType::FreeList;

	m_Allocator = gEngine->GetMemoryManager()->CreateMemoryAllocator(createInfo);

    return true;
}

void Rocket::RocketAssetManager::Shutdown()
{
}

Rocket::RocketAsset* Rocket::RocketAssetManager::LoadRocketAsset(const rkstring& path)
{
    
}
