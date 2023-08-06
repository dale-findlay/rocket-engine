#include "MemoryManager.h"

#include <stdlib.h>

Rocket::MemoryManager* Rocket::gMemoryManager = nullptr;

Rocket::MemoryManager::MemoryManager()
	: m_GlobalMemoryAllocator(nullptr)
{}

bool Rocket::MemoryManager::Init()
{
	AllocateGlobalEngineMemory();	
	return true;
}

void Rocket::MemoryManager::Shutdown()
{
	CleanupRegisteredAllocators();
	FreeGlobalEngineMemory();
}

Rocket::MemoryAllocator* Rocket::MemoryManager::CreateMemoryAllocator(const MemoryAllocatorCreateInfo& createInfo)
{
	size_t usedEngineMemory = m_GlobalMemoryAllocator->GetUsedMemory();

	//Make sure we still have some memory available.
	RK_ASSERT(createInfo.maxSize < m_GlobalMemoryAllocator->GetSize() - usedEngineMemory);

	//Allocate the memory from the global engine memory.
	void* pMemoryBlock = m_GlobalMemoryAllocator->Allocate(createInfo.maxSize);
	
	Allocator* newAllocator = nullptr;
	
	switch (createInfo.type)
	{
	case Rocket::MemoryAllocatorType::Stack:
		newAllocator = new Memory::StackAllocator(createInfo.maxSize, pMemoryBlock);
		break;
	case Rocket::MemoryAllocatorType::FreeList:
		newAllocator = new Memory::FreeListAllocator(createInfo.maxSize, pMemoryBlock);
		break;
	case Rocket::MemoryAllocatorType::Linear:
		newAllocator = new Memory::LinearAllocator(createInfo.maxSize, pMemoryBlock);
		break;
	case Rocket::MemoryAllocatorType::Pool:
		newAllocator = new Memory::PoolAllocator(createInfo.pool_blockSize, createInfo.pool_blockAlignment, createInfo.maxSize, pMemoryBlock);
		break;
	}

	MemoryAllocator* mProxyAllocator = new MemoryAllocator(newAllocator);
	
	RegisterMemoryAllocator(createInfo, mProxyAllocator);

	return mProxyAllocator;
}

void* Rocket::MemoryManager::AllocateInternal(size_t blockSize)
{
	return malloc(blockSize);
}

void Rocket::MemoryManager::DeallocateInternal(void* p)
{
	free(p);
}

void Rocket::MemoryManager::AllocateGlobalEngineMemory()
{
	/* 
	 * The engine will need to allocate memory quickly and also allocate memory in such a way 
	 * that logically preserves the principle of locality to avoid unnecessary cache misses.
	 * in Rocket, there's three critical systems that allocate larger chunks of memory:
	 * - runtime tagged text (rktag) (preallocated global string map)
	 * - object manager (garbage collection, object lifetime management, everything gameplay in the game)
	 * - rendering manager and by extension the active renderer (cpu-side buffers, render commands, in-flight frames etc.)
	 * - physics
	 * - scene graph.
	 * 
	 * For these systems, it's fairly straight forward to minimize cache misses by virtually allocating pretty 
	 * large address spaces for them to operate within. vIrTuaL MeMorY yAyyyyy
	 * 
	 * Basically memory manager's responsibility is the manage these allocations coming in from these systems and keep them 
	 * fed with allocators.
	 */

	//Allocate global engine memory. 1GB
	size_t engineMemoryBlockSize = 1024 * 1024 * 1024;
	void* globalEngineBlock = AllocateInternal(engineMemoryBlockSize);

	m_GlobalMemoryAllocator = new Memory::FreeListAllocator(engineMemoryBlockSize, globalEngineBlock);
}

void Rocket::MemoryManager::FreeGlobalEngineMemory()
{	
	if (m_GlobalMemoryAllocator == nullptr)
	{
		return;
	}

	if (m_GlobalMemoryAllocator->GetStart() != nullptr)
	{
		DeallocateInternal(m_GlobalMemoryAllocator->GetStart());
		delete m_GlobalMemoryAllocator;
		m_GlobalMemoryAllocator = nullptr;
		m_GlobalMemoryAllocator = nullptr;
	}
}

void Rocket::MemoryManager::RegisterMemoryAllocator(const MemoryAllocatorCreateInfo& createInfo, MemoryAllocator* allocator)
{
	m_MemoryAllocators.emplace_back(createInfo);

	MemoryAllocatorCreateInfo& allocatorCreateInfo = m_MemoryAllocators.back();
	allocatorCreateInfo.pAllocator = allocator;
}

void Rocket::MemoryManager::CleanupRegisteredAllocators()
{
	for (auto& el : m_MemoryAllocators)
	{
		if (el.pAllocator)
		{
			//deallocate the memory of the allocator.
			void* mem = el.pAllocator->GetStart();
			m_GlobalMemoryAllocator->Deallocate(mem);

			Allocator* innerAllocator = el.pAllocator->GetInnerAllocator();
			//cleanup the internal allocator.
			if (innerAllocator)
			{
				delete innerAllocator;
			}
						
			//cleanup the proxy:
			delete el.pAllocator;

			el.pAllocator = nullptr;
		}
	}
}
