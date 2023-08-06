#include "FreeListAllocator.h"

Rocket::Memory::FreeListAllocator::FreeListAllocator(size_t size, void* start)
    : Allocator(size, start), m_FreeBlocks((FreeListAllocatorBlock*)start)
{
    RK_ASSERT(size > sizeof(FreeListAllocatorBlock));
    m_FreeBlocks->size = size;
    m_FreeBlocks->nextBlock = nullptr;
}

Rocket::Memory::FreeListAllocator::~FreeListAllocator()
{
    m_FreeBlocks = nullptr;
}

void* Rocket::Memory::FreeListAllocator::Allocate(size_t size, uint8 alignment)
{
    RK_ASSERT(size != 0 && alignment != 0);

    const size_t AllocationHeaderSize = sizeof(FreeListAllocationHeader);

    FreeListAllocatorBlock* previousBlock = nullptr;
    FreeListAllocatorBlock* currentBlock = m_FreeBlocks;

    while (currentBlock != nullptr)
    {   
        uint8 adjustment = AllocatorUtility::CalculateAlignForwardHeaderAdjustment(currentBlock, alignment, AllocationHeaderSize);
        size_t requiredBlockSize = size + adjustment;

        if (currentBlock->size < requiredBlockSize)
        {
            previousBlock = currentBlock;
            currentBlock = currentBlock->nextBlock;
            continue;
        }

        if (currentBlock->size - requiredBlockSize <= AllocationHeaderSize)
        {
            requiredBlockSize = currentBlock->size;

            if (previousBlock != nullptr)
            {
                previousBlock->nextBlock = currentBlock->nextBlock;
            }
            else
            {
                currentBlock = currentBlock->nextBlock;
            }
        }
        else
        {
            FreeListAllocatorBlock* nextBlock = (FreeListAllocatorBlock*)(reinterpret_cast<uint64>(currentBlock)+requiredBlockSize);
            nextBlock->size = currentBlock->size - requiredBlockSize;
            nextBlock->nextBlock = currentBlock->nextBlock;

			if (previousBlock != nullptr)
			{
				previousBlock->nextBlock = nextBlock;
			}
			else
			{
				currentBlock = nextBlock;
			}
        }

        uint64 pAlignedAddress = (uint64)currentBlock + adjustment;

        FreeListAllocationHeader* AllocationHeader = (FreeListAllocationHeader*)(pAlignedAddress - AllocationHeaderSize);
        AllocationHeader->size = requiredBlockSize;
        AllocationHeader->adjustment = adjustment;

        m_AllocationCount++;
        m_AllocatedMemory += requiredBlockSize;

        return (void*)pAlignedAddress;
    }

    //If we got to here its because we couldn't find a block big enough for our request.
    return nullptr;
}

void Rocket::Memory::FreeListAllocator::Deallocate(void* p)
{
    const size_t AllocationHeaderSize = sizeof(FreeListAllocationHeader);
	FreeListAllocationHeader* AllocationHeader = (FreeListAllocationHeader*)(reinterpret_cast<uint64>(p) - AllocationHeaderSize);

    uint64 blockStart = reinterpret_cast<uint64>(p) - AllocationHeader->adjustment;
    size_t blockSize = AllocationHeader->size;
    uint64 blockEnd = blockStart + blockSize;

    FreeListAllocatorBlock* previousBlock = nullptr;
    FreeListAllocatorBlock* currentBlock = m_FreeBlocks;
    
    //Search through our blocks for one!
    while (currentBlock != nullptr)
    {
        if ((uint64)currentBlock >= blockEnd)
        {
            break; //Hey we're here - probably.
        }

        previousBlock = currentBlock;
        currentBlock = currentBlock->nextBlock;
    }

    if (previousBlock == nullptr)
    {
        previousBlock = (FreeListAllocatorBlock*)blockStart;
        previousBlock->size  = blockSize;
        previousBlock->nextBlock = m_FreeBlocks;
    }
    else if ((uint64)previousBlock + previousBlock->size == blockSize)
    {
        previousBlock->size += blockSize;
    }
    else 
    {
        FreeListAllocatorBlock* temporaryBlock = (FreeListAllocatorBlock *)blockStart;
        temporaryBlock->size = blockSize;
        temporaryBlock->nextBlock = previousBlock->nextBlock;
        previousBlock->nextBlock = temporaryBlock;
        previousBlock = temporaryBlock;
    }

    if (currentBlock != nullptr && (uint64)currentBlock == blockEnd)
    {
        previousBlock->size += currentBlock->size;
        previousBlock->nextBlock = currentBlock->nextBlock;
    }

    m_AllocatedMemory -= blockSize;
    m_AllocationCount--;
}
