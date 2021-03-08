#include "EntityFactory.h"
#include "runtime/Engine.h"

Rocket::EntityFactory::EntityFactory()
{
	size_t poolSize = sizeof(Entity) * MAX_ENTITY_COUNT;

	//Allocate a chunk of memory from the scene manger and create allocator.
	void* pMemory = gEngine->GetSceneManager()->GetMemoryAllocator()->Allocate(poolSize);
	m_EntityPool = new Memory::PoolAllocator(sizeof(Entity), 4, poolSize, pMemory);
}

SharedPtr<Rocket::Entity> Rocket::EntityFactory::CreateEntity(const rkstring& entityName)
{
	Entity* newEntity = (Entity*)m_EntityPool->Allocate(sizeof(Entity));
	
	newEntity->uid = UniqueId();
	newEntity->name = entityName;

	auto sharedPtr = SharedPtr<Entity>(newEntity);

	return sharedPtr;
}

void Rocket::EntityFactory::RecycleEntity(SharedPtr<Rocket::Entity> entity)
{
	void* pEntity = (void*)(entity.get());

	m_EntityPool->Deallocate(pEntity);
}

void Rocket::EntityFactory::RecycleAllEntities()
{
	for (const auto& it : m_Entities)
	{
		RecycleEntity(it);
	}	
}
