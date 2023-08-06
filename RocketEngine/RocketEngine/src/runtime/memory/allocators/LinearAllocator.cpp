#include "LinearAllocator.h"

Rocket::Memory::LinearAllocator::LinearAllocator(size_t size, void* start)
    : Allocator(size, start), m_CurrentPosition(start)
{
    RK_ASSERT(size > 0);
}

Rocket::Memory::LinearAllocator::~LinearAllocator()
{
    m_CurrentPosition = nullptr;
}

void* Rocket::Memory::LinearAllocator::Allocate(size_t size, uint8 alignment)
{    
    RK_ASSERT(size > 0);

    uint8 adjustment = AllocatorUtility::CalculateAdjustment(m_CurrentPosition, alignment);

    void* pAligned = (void*)(reinterpret_cast<uint64>(m_CurrentPosition )+ adjustment);

    m_CurrentPosition = (void*)(reinterpret_cast<uint64>(pAligned) + size);
    m_AllocatedMemory += size + adjustment;
    m_AllocationCount++;

    return pAligned;
}

void Rocket::Memory::LinearAllocator::Deallocate(void* p)
{
    //this is probably overkill - use Clear()!
    RK_ASSERT(false);
}

void Rocket::Memory::LinearAllocator::Clear()
{
    m_CurrentPosition = GetStart();
    m_AllocationCount = 0;
    m_AllocatedMemory = 0;
}
