#include "MemoryManager.h"

bool Rocket::MemoryManager::Init()
{
    ResetStateFlags();
    
    
    return false;
}

void Rocket::MemoryManager::Shutdown()
{
}

void* Rocket::MemoryManager::Allocate(size_t blockSize)
{
    return nullptr;
}

void Rocket::MemoryManager::Free(void* block, size_t blockSize)
{
}
