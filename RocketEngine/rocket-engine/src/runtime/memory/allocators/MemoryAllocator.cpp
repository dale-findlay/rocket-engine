#include "MemoryAllocator.h"

Rocket::Memory::MemoryAllocator::MemoryAllocator(Allocator* allocator)
    : Allocator(allocator->GetSize(), allocator->GetStart()), m_Allocator(allocator)
{    
}

Rocket::Memory::MemoryAllocator::~MemoryAllocator()
{}

void* Rocket::Memory::MemoryAllocator::Allocate(size_t size, uint8 alignment)
{
    ROCKETASSERT(size > 0);
    
    size_t previousUsedMemory = m_Allocator->GetUsedMemory();

    void* p = m_Allocator->Allocate(size, alignment);

    m_AllocationCount++;
    m_AllocatedMemory += m_Allocator->GetUsedMemory() - previousUsedMemory;

    return p;
}

void Rocket::Memory::MemoryAllocator::Deallocate(void* p)
{
	size_t previousUsedMemory = m_Allocator->GetUsedMemory();

	m_Allocator->Deallocate(p);

    size_t allocationSize = previousUsedMemory - m_Allocator->GetUsedMemory();

	m_AllocationCount--;
	m_AllocatedMemory -= allocationSize;
}

Rocket::Memory::Allocator* Rocket::Memory::MemoryAllocator::GetInnerAllocator()
{
    return m_Allocator;
}
