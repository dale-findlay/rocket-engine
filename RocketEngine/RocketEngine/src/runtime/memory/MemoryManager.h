#pragma once

#include "core/EngineSubsystem.h"
#include "runtime/memory/Allocators.h"

#include <vector>

namespace Rocket 
{
	enum class MemoryAllocatorType {
		Stack,
		FreeList,
		Linear,
		Pool
	};

	struct MemoryAllocatorCreateInfo 
	{		
		MemoryAllocatorType type;
		rkstring name;
		uint64 maxSize;

		//For pool allocator
		size_t pool_blockSize;
		uint8 pool_blockAlignment;

		MemoryAllocator* pAllocator;
	};

	// Responsible for managing the memory for the engine.
	class MemoryManager : public CoreSubsystem
	{
	public:
		MemoryManager();

		virtual bool Init() override;
		virtual void Shutdown() override;

		MemoryAllocator* CreateMemoryAllocator(const MemoryAllocatorCreateInfo& createInfo);

	private:
		void* AllocateInternal(size_t blockSize);
		void DeallocateInternal(void* p);

		void AllocateGlobalEngineMemory();
		void FreeGlobalEngineMemory();

		/**
		 * Register a memory allocator.
		 */
		void RegisterMemoryAllocator(const MemoryAllocatorCreateInfo& createInfo, MemoryAllocator* allocator);
		void CleanupRegisteredAllocators();

	private:	
		/**
		 * Allocators
		 * As memory allocation is rarely a one size fits all problem, multiple allocators are used.
		 * The memory manager is in charge on owning and managing the various allocators.
		 */

		 //This is the allocator that owns pretty much all the memory in the engine.
		 Rocket::Memory::FreeListAllocator* m_GlobalMemoryAllocator;

		 std::vector<MemoryAllocatorCreateInfo> m_MemoryAllocators;
	};

	extern MemoryManager* gMemoryManager;
}