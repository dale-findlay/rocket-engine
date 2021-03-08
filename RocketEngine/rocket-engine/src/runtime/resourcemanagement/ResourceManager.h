#pragma once

#include "core/EngineSubsystem.h"
#include "runtime/memory/allocators/MemoryAllocator.h"

namespace Rocket
{
	class ResourceManager : public EngineSubsystem
	{
	public:
		ResourceManager();

		// Inherited via EngineSubsystem
		virtual bool Init() override;
		virtual void Shutdown() override;

		//Create resources.

		FORCEINLINE Memory::MemoryAllocator* GetMemoryAllocator() {
			return m_Allocator;
		}

	private:
		Memory::MemoryAllocator* m_Allocator;
	};
}