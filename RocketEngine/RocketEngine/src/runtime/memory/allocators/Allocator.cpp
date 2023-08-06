#include "Allocator.h"

Rocket::Allocator::Allocator(size_t size, void* start)
    : m_Start(start), m_Size(size), m_AllocatedMemory(0), m_AllocationCount(0)
{}

Rocket::Allocator::~Allocator()
{
    /*
        This check is two fold, 1 that we actually deallocated for every allocation 
        and 2 that the blocks were deallocated properly.
    */
    RK_ASSERT(m_AllocationCount == 0 && m_AllocatedMemory == 0);

    m_Start = nullptr;
    m_Size = 0;
}