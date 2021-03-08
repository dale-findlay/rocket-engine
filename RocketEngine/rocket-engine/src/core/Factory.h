#pragma once

#include "core/CoreMinimal.h"
#include "runtime/memory/allocators/MemoryAllocator.h"
#include "runtime/memory/allocators/PoolAllocator.h"

#include <vector>

namespace Rocket {

	/**
	 * Factory
	 * This class handles the allocation, creation, recycle and cleanup of various objects.
	 * The SetupObject method can be overridden to provide additional setup
		on a given object (such as setting a uid) - but this isn't required
	 * The lifetime of the Factory is directly tied to the lifetime of the object.
	 *
	 * An optional subAllocator can be provided when creating the factory, the implementation will use this
		instead of querying the gMemoryAllocator for an allocator.
	 */

	template<typename T>
	class Factory
	{
	public:
		Factory(uint32 maxObjectCount, Memory::MemoryAllocator* subAllocator = nullptr);

		SharedPtr<T> CreateObject();
		void RecycleObject(SharedPtr<T> obj);

	protected:
		virtual void SetupObject(SharedPtr<T> obj);

	private:
		Memory::MemoryAllocator* CreateMemoryAllocator();
		void DestoryMemoryAllocator();

		void AllocateObjectPool();

	private:
		std::vector<SharedPtr<T>> m_CreatedObjects;
		Memory::MemoryAllocator* m_Allocator;

		/** Max number of objects that can appear in this factory. */
		uint32 m_MaxObjectCount;
	};

	/**
	 * FactoryUtils
	 * For generic template agnostic functions related .
	 * 
	 * This is mainly to avoid including "runtime/Engine.h" in this file as that sucksss.
	 */
	class FactoryUtils 
	{
		static Memory::MemoryAllocator* CreateMemoryAllocator(size_t size);
	};


	template<typename T>
	inline Factory<T>::Factory(uint32 maxObjectCount, Memory::MemoryAllocator* subAllocator)
		: m_Allocator(subAllocator), m_MaxObjectCount(maxObjectCount)
	{
		//Do we need an allocator?
		if (!subAllocator)
		{
			CreateMemoryAllocator(poolSize);
		}

		AllocateObjectPool();
	}

	template<typename T>
	inline SharedPtr<T> Factory<T>::CreateObject()
	{
		T* newEntity = (T*)m_ObjectPool->Allocate(sizeof(T));
		auto sharedPtr = SharedPtr<Entity>(newEntity);
		m_CreatedObjects.push_back(sharedPtr);
		return sharedPtr;
	}
	
	template<typename T>
	inline void Factory<T>::RecycleObject(SharedPtr<T> obj)
	{
		void* pObj = (void*)(obj.get());
		m_ObjectPool->Deallocate(pObj);
	}	

	template<typename T>
	inline void Factory<T>::SetupObject(SharedPtr<T> obj)
	{
		/**
		 * Do Nothing.
		 */
	}
	
	template<typename T>
	inline Memory::MemoryAllocator* Factory<T>::CreateMemoryAllocator()
	{
		size_t poolSize = sizeof(T) * m_MaxObjectCount;
		//First create a proxied allocator from the global manager.
	}

	template<typename T>
	inline void Factory<T>::DestoryMemoryAllocator()
	{
	}

	template<typename T>
	inline void Factory<T>::AllocateObjectPool()
	{	
		if (m_Allocator)
		{
			m_Allocator-
		}
	}
}