#pragma once

#include "runtime/memory/allocators/Allocator.h"

namespace Rocket 
{
	namespace Memory
	{
		class LinearAllocator : public Allocator 
		{
		public:
			LinearAllocator(size_t size, void* start);
			~LinearAllocator();

			// Inherited via Allocator
			void* Allocate(size_t size, uint8 alignment = 4) override;	
						
			/**
			 * NOTE - DO NOT USE THIS FUNCTION:
			 * Linear allocators do not allow for deallocating single allocations. Please use Clear()!
			 */
			void Deallocate(void* p) override;

			/**
			 * Clear all allocations.
			 */
			void Clear();

		private:
			void* m_CurrentPosition;
		};
	}
}