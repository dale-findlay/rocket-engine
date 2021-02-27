#pragma once

#include "core/EngineSubsystem.h"

#include "runtime/memory/MemoryManager.h"
#include "runtime/renderering/Renderer.h"

namespace Rocket
{
	class RendererManager : public EngineSubsystem
	{
	public:
		RendererManager();

		// Inherited via EngineSubsystem
		virtual bool Init() override;
		virtual void Shutdown() override;
		void DrawFrame();
		
		class Rocket::Renderer* GetRenderer();

		FORCEINLINE class Rocket::Memory::MemoryAllocator* GetMemoryAllocator() 
		{
			return m_MemoryAllocator;
		}


	private:
		 class Rocket::Memory::MemoryAllocator* m_MemoryAllocator;
		 class Rocket::Renderer* m_Renderer;
	};
}