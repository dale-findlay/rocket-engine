#include "MemoryManager.h"

#include <stdlib.h>

Rocket::MemoryManager::MemoryManager()
	: EngineSubsystem(), m_GlobalMemoryAllocator(nullptr)
{}

bool Rocket::MemoryManager::Init()
{
	ResetStateFlags();
	AllocateGlobalEngineMemory();	
	SetIsInitialized(true);

	return true;
}

void Rocket::MemoryManager::Shutdown()
{
	CleanupRegisteredAllocators();
	FreeGlobalEngineMemory();	
	SetIsInitialized(false);
	SetIsShutdown(true);
}

Rocket::Memory::MemoryAllocator* Rocket::MemoryManager::CreateMemoryAllocator(const MemoryAllocatorCreateInfo& createInfo)
{
	ROCKETASSERT(IsInitialized());	
	
	size_t usedEngineMemory = m_GlobalMemoryAllocator->GetUsedMemory();

	//Make sure we still have some memory available.
	ROCKETASSERT(createInfo.maxSize < m_GlobalMemoryAllocator->GetSize() - usedEngineMemory);

	//Allocate the memory from the global engine memory.
	void* pMemoryBlock = m_GlobalMemoryAllocator->Allocate(createInfo.maxSize);
	
	Memory::Allocator* newAllocator = nullptr;
	
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

	Memory::MemoryAllocator* mProxyAllocator = new Memory::MemoryAllocator(newAllocator);
	
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

void Rocket::MemoryManager::RegisterMemoryAllocator(const MemoryAllocatorCreateInfo& createInfo, Memory::MemoryAllocator* allocator)
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

			Memory::Allocator* innerAllocator = el.pAllocator->GetInnerAllocator();
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
