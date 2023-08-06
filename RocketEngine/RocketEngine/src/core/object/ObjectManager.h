#pragma once
#include "core/CoreTypes.h"
#include "core/CoreMacros.h"
#include "core/CoreSubsystem.h"

#define RK_MAX_OBJECTS 100000000ULL

namespace Rocket
{
	class RkObject;
	class MemoryAllocator;

	// the 'garbage collector' of rocket.
	// implements a basic generation based object system.
	class ObjectManager : public CoreSubsystem
	{
	public:
		virtual bool Init() override;
		virtual void Shutdown() override;

		void Tick();

		template <typename TObjectType>
		inline TObjectType* NewObject(RkObject* parentObject, const rkstring& name)
		{
			// allocate some memory from the allocator:
			TObjectType* newObject = new TObjectType();
			newObject->SetName(name);
			newObject->SetParent(parentObject);

			m_Objects.push_back(newObject);

			return newObject;
		}
		
		FORCEINLINE int32 GetInstanceCount(const rkstring& typeName)
		{
			auto foundInstanceIt = m_InstanceCount.find(typeName);

			if (foundInstanceIt != m_InstanceCount.end())
			{
				return m_InstanceCount[typeName];
			}

			return 0;
		}

	private:
		std::unordered_map<rkstring, uint32> m_InstanceCount;
		std::vector<RkObject*> m_Objects;

		//class Rocket::MemoryAllocator* m_Gen1Allocator;
		//class Rocket::MemoryAllocator* m_Gen2Allocator;
		//class Rocket::MemoryAllocator* m_Gen3Allocator;
	};

	extern ObjectManager* gObjectManager;
}