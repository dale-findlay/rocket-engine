#pragma once

#include "core/CoreMinimal.h"
#include "runtime/memory/utilities/AllocatorUtility.h"

namespace Rocket {
	class Allocator
	{
	public:
		Allocator(size_t size, void* start);
		~Allocator();

		FORCEINLINE void* GetStart()
		{
			return m_Start;
		};

		FORCEINLINE size_t GetSize() const
		{
			return m_Size;
		}

		virtual void* Allocate(size_t size, uint8 alignment = 4) = 0;
		virtual void Deallocate(void* p) = 0;

		FORCEINLINE size_t GetAllocationCount() const
		{
			return m_AllocationCount;
		};

		FORCEINLINE size_t GetUsedMemory() const
		{
			return m_AllocatedMemory;
		}

	protected:
		void* m_Start;
		size_t m_Size;

		size_t m_AllocationCount;
		size_t m_AllocatedMemory;
	};
}