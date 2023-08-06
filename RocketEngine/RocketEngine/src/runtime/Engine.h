#pragma once

#include "core/CoreMinimal.h"
#include "runtime/Subsystems.h"

namespace Rocket
{
	class Engine
	{
	public:
		// Initialize the engine.
		bool Init();

		// Run the engine, kicks off main game loop.
		int32 Run();

		// Safely shutdown the engine.
		void Shutdown();

		// Returns a pointer a registered subsystem.
		template<typename TObjectType>
		FORCEINLINE TObjectType* GetSubsystem()
		{
			auto findResult = m_RegisteredSubsystems.find(TObjectType::GetTypeName());

			if (findResult == m_RegisteredSubsystems.end())
			{
				return nullptr;
			}

			const std::pair<rkstring, RkObject*>& pair = *findResult;

			return static_cast<TObjectType*>(pair.second);
		}

		// Register a new subsystem by object type, returns a ptr to the new subsystem.
		template<typename TObjectType>
		FORCEINLINE TObjectType* RegisterSubsystem()
		{
			TObjectType* subsystemPtr = CreateObject<TObjectType>(nullptr, TObjectType::GetTypeName() + "_0");
			if (!subsystemPtr->Init())
			{
				RK_LOG(Error, "Failed to initialize a subsystem!");
				subsystemPtr->Shutdown();
				return nullptr;
			}

			m_RegisteredSubsystems.insert({ TObjectType::GetTypeName(), static_cast<RkObject*>(subsystemPtr) });

			return subsystemPtr;
		}

		// Unregister a subsystem by object type.
		template<typename TObjectType>
		FORCEINLINE void UnregisterSubsystem()
		{
			TObjectType* subsystemPtr = GetSubsystem<TObjectType>();
			if (!subsystemPtr)
			{
				subsystemPtr->Shutdown();

				RK_LOG(Error, "Failed to initialize a subsystem!");
			}

			m_RegisteredSubsystems.erase(TObjectType::GetTypeName());
		}

	protected:
		// Create and initialize engine subsystems.
		bool InitEngineSubsystems();

		// Cleanup registered engine subsystems.
		void ShutdownEngineSubsystems();

		// Resets the state of the engine to an uninitialized state.
		void ResetRuntimeExecutionFlags();
	private:
		
		// These flags indicate the runtime state of the engine.
		bool bShouldClose;
		bool bInitializationError;
		
		// All the registered subsystems, maps subsystem object type to object ptr. 
		std::unordered_map<rkstring, RkObject*> m_RegisteredSubsystems;
	};

	extern Engine* gEngine;
}