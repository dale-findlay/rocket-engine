#include "StackAllocator.h"

Rocket::Memory::StackAllocator::StackAllocator(size_t size, void* start)
	: Allocator(size, start), m_CurrentPosition(start)
{
	RK_ASSERT(size > 0);
}

Rocket::Memory::StackAllocator::~StackAllocator()
{
	m_CurrentPosition = nullptr;
}

void* Rocket::Memory::StackAllocator::Allocate(size_t size, uint8 alignment)
{
	RK_ASSERT(size > 0);

	const size_t allocationHeaderSize = sizeof(StackAllocatorHeader);
	
	uint8 adjustment = AllocatorUtility::CalculateAlignForwardHeaderAdjustment(m_CurrentPosition, alignment, allocationHeaderSize);
		
	size_t allocationSize = adjustment + size;

	if (m_AllocatedMemory + allocationSize > m_Size)
	{
		//thats all she wrote. - no memory left to give.
		return nullptr;
	}

	void* pAligned =(void*)(reinterpret_cast<uint64>(m_CurrentPosition) + adjustment);
	
	// Setup the header.
	StackAllocatorHeader* allocatorHeader = (StackAllocatorHeader*)(reinterpret_cast<uint64>(pAligned) - allocationHeaderSize);
	allocatorHeader->adjustment = adjustment;

	// At this point the allocation is considered complete!
	m_AllocationCount++;
	m_AllocatedMemory += allocationSize;
	
	m_CurrentPosition = (void*)(reinterpret_cast<uint64>(m_CurrentPosition) + allocationSize);

	return pAligned;
}

void Rocket::Memory::StackAllocator::Deallocate(void* p)
{
	const size_t allocationHeaderSize = sizeof(StackAllocatorHeader);

	//Grab the header.
	StackAllocatorHeader* allocatorHeader = (StackAllocatorHeader*)(reinterpret_cast<uint64>(p) - allocationHeaderSize);
	
	size_t allocationSize = (uint64)m_CurrentPosition - (uint64)p - allocatorHeader->adjustment;

	//Fix up our stats.
	m_AllocatedMemory -= allocationSize; 
	m_CurrentPosition = (void*)(reinterpret_cast<uint64>(p) - allocatorHeader->adjustment);

	m_AllocationCount--;
}
