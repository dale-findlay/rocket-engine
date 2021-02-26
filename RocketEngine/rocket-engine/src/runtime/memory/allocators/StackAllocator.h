#pragma once

#include "runtime/memory/allocators/Allocator.h"

namespace Rocket
{
	namespace Memory
	{
		struct StackAllocatorHeader 
		{			
			uint8 adjustment;
		};

		class StackAllocator : public Allocator 
		{
			public:
			StackAllocator(size_t size, void* start);
			~StackAllocator();

			// Inherited via Allocator
			void* Allocate(size_t size, uint8 alignment = 4) override;
			void Deallocate(void* p) override;

			private:
				void* m_CurrentPosition;
		};
	}
}