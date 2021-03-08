#pragma once

#define MAX_ENTITY_COUNT 10000

#include "core/CoreMinimal.h"
#include "runtime/core/Entity.h"
#include "runtime/memory/allocators/PoolAllocator.h"

#include <vector>

namespace Rocket
{
	/**
	 * Entity factories should be owned by the SceneManager.
	 */
	class EntityFactory
	{
	public:		
		EntityFactory();		
		SharedPtr<Rocket::Entity> CreateEntity(const rkstring& entityName);
		void RecycleEntity(SharedPtr<Rocket::Entity> entity);
		void RecycleAllEntities();

	private:
		std::vector<SharedPtr<Rocket::Entity>> m_Entities;

		Memory::PoolAllocator* m_EntityPool;
	};
}