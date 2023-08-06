#include "PoolAllocator.h"

Rocket::Memory::PoolAllocator::PoolAllocator(size_t blockSize, uint8 blockAlignment, size_t size, void* start)
	: Allocator(size, start), m_BlockSize((uint8)blockSize), m_BlockAlignment(blockAlignment), m_FreeBlockList(nullptr)
{
	RK_ASSERT(size > 0);
	InitializeFreeBlocks();
}

Rocket::Memory::PoolAllocator::~PoolAllocator()
{
	m_FreeBlockList = nullptr;
}

void Rocket::Memory::PoolAllocator::InitializeFreeBlocks()
{
	void* initialPtr = GetStart();

	//Find the adjustment relative to our initial ptr for each block.
	uint8 adjustment = AllocatorUtility::CalculateAdjustment(initialPtr, m_BlockAlignment);
	
	m_BlockCapacity = (GetSize() - adjustment) / m_BlockSize;
	
	m_FreeBlockList = (void**)(reinterpret_cast<uint64>(initialPtr) + adjustment);

	//Initialize our list of free blocks.
	void** p = m_FreeBlockList;
	for (size_t i = 0; i < m_BlockCapacity; ++i)
	{
		*p = (void*)(reinterpret_cast<uint64>(p) + m_BlockSize);
		p = (void**) *p;
	}

	*p = nullptr;
}

void* Rocket::Memory::PoolAllocator::Allocate(size_t size, uint8 alignment)
{
	RK_ASSERT(size == m_BlockSize && m_BlockAlignment == alignment); //Make sure we cant accidentally allocate any bad blocks.
	
	if (m_FreeBlockList == nullptr)
	{
		//Your block isn't initialized!
		return nullptr;
	}

	void* pAlignedBlockAddress = m_FreeBlockList;

	m_FreeBlockList = (void**)(*m_FreeBlockList);

	m_AllocatedMemory += size;
	m_AllocationCount++;

	return pAlignedBlockAddress;
}

void Rocket::Memory::PoolAllocator::Deallocate(void* p)
{
	*((void**)p) = m_FreeBlockList;
	m_FreeBlockList = (void**)p;

	m_AllocatedMemory -= m_BlockSize;
	m_AllocationCount--;
}
