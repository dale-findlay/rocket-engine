#pragma once

#include "core/EngineSubsystem.h"

#include "runtime/memory/MemoryManager.h"
#include "runtime/rendering/Renderer.h"

namespace Rocket
{
	class RkRendererManager : public RkEngineSubsystem
	{
		RK_OBJECT_BODY()
	public:
		RkRendererManager();

		// Inherited via EngineSubsystem
		virtual bool Init() override;
		virtual void Shutdown() override;
		void DrawFrame();

		class Rocket::Renderer* GetRenderer();

		FORCEINLINE class Rocket::MemoryAllocator* GetMemoryAllocator()
		{
			return m_MemoryAllocator;
		}

	private:
		class Rocket::MemoryAllocator* m_MemoryAllocator;
		class Rocket::Renderer* m_Renderer;
	};
}