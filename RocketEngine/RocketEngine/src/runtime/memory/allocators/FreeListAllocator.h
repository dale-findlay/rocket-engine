#pragma once

#include "runtime/memory/allocators/Allocator.h"

namespace Rocket
{
	namespace Memory
	{
		struct FreeListAllocationHeader
		{
			size_t size;
			uint8 adjustment;
		};

		struct FreeListAllocatorBlock
		{
			size_t size;
			FreeListAllocatorBlock* nextBlock;
		};

		class FreeListAllocator : public Allocator
		{
		public:
			FreeListAllocator(size_t size, void* start);
			~FreeListAllocator();

			// Inherited via Allocator
			void* Allocate(size_t size, uint8 alignment = 4) override;
			void Deallocate(void* p) override;
		private:
			FreeListAllocatorBlock* m_FreeBlocks;
		};
	}
}
