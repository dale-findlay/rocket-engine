#pragma once

#include "runtime/memory/allocators/Allocator.h"

namespace Rocket
{
	class MemoryAllocator : public Allocator
	{
	public:
		MemoryAllocator(Allocator* allocator);
		~MemoryAllocator();

		// Inherited via Allocator
		virtual void* Allocate(size_t size, uint8 alignment = 4) override;
		virtual void Deallocate(void* p) override;

		Allocator* GetInnerAllocator();

	private:
		Allocator* m_Allocator;
	};
}
