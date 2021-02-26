#pragma once

#include "core/CoreTypes.h"
#include "runtime/Subsystems.h"

namespace Rocket
{

	class Engine
	{
	public:
		bool Init();
		int32 Run();
		void Shutdown();

	protected:
		bool InitEngineSystems();
		void ShutdownEngineSystems();

		bool InitGameSystems();
		void ShutdownGameSystems();

		/**
		 * Resets the state of the engine to an un-initialized state.
		 */
		void ResetRuntimeExecutionFlags();

		/**
		 * Execution Loop Functions
		 * These functions are executed in the engine's execution loop.
		 */
		 void UpdatePreRenderSystems();
		 void UpdatePostRenderSystems();

	private:
		
		/**
		 * Runtime Execution Flags
		 * These flags indicate the runtime state of the engine.
		 */
		bool bShouldClose;
		bool bInitializationError;
		
		/**
		 * Engine Subsystems
		 * These objects are owned exclusively by the engine and represent the modules that make up the core engine functionality.
		 */
		MemoryManager* m_MemoryManager;
		//WindowSystem* m_WindowSystem;
		//Renderer* m_Renderer;
		//SceneManager* m_SceneManager;
	};
}