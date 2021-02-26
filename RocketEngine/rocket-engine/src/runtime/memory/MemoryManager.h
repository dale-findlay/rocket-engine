#pragma once

#include "core/EngineSubsystem.h"
#include "runtime/memory/Allocators.h"

namespace Rocket {

	class MemoryManager : public EngineSubsystem
	{
	public:
		virtual bool Init() override;
		virtual void Shutdown() override;
		
		void GetStackAllocator();

	private:		
		/**
		 * Allocators
		 * As memory allocation is rarely a one size fits all problem, multiple allocators are used.
		 * The memory manager is in charge on owning and managing the various allocators.
		 */
		 //StackAllocator* m_GlobalChunkAllocator;

	};
}