#pragma once

#include "core/EngineSubsystem.h"
#include "runtime/memory/allocators/MemoryAllocator.h"
#include "runtime/entitysystem/EntityFactory.h"

namespace Rocket
{
	class SceneManager : public EngineSubsystem 
	{
	public:
		SceneManager();

		// Inherited via EngineSubsystem
		virtual bool Init() override;
		virtual void Shutdown() override;

		FORCEINLINE Memory::MemoryAllocator* GetMemoryAllocator() {
			return m_Allocator;
		}

		FORCEINLINE Rocket::EntityFactory* GetEntityFactory() 
		{
			return m_EntityFactory;
		}

	private:
		Memory::MemoryAllocator* m_Allocator;
		Rocket::EntityFactory* m_EntityFactory;
	};
}