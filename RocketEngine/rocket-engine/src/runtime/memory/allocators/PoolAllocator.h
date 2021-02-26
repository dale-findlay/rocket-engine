#pragma once

#include "runtime/memory/allocators/Allocator.h"

namespace Rocket
{
	namespace Memory
	{
		class PoolAllocator : public Allocator
		{
		public:
			PoolAllocator(size_t blockSize, uint8 blockAlignment, size_t size, void* start);
			~PoolAllocator();

			// Inherited via Allocator
			void* Allocate(size_t size, uint8 alignment = 4) override;
			void Deallocate(void* p) override;

			FORCEINLINE size_t GetBlockCapacity() const
			{
				return m_BlockCapacity;
			}

		private:
			void InitializeFreeBlocks();

		private:
			uint8 m_BlockSize;
			uint8 m_BlockAlignment;

			size_t m_BlockCapacity;

			void** m_FreeBlockList;
		};
	}
}
