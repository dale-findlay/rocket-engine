#pragma once

#include "core/CoreMinimal.h"
#include "runtime/rendering/commands/RenderCommand.h"
#include "runtime/memory/allocators/LinearAllocator.h"
#include <vector>
#include <type_traits>

namespace Rocket
{
	class RkRendererManager;

	class Renderer
	{
	public:
		Renderer();

		virtual bool Init();
		virtual void Shutdown();
		virtual void DrawFrame();

		template<typename T>
		inline SharedPtr<T> CreateRenderCommand()
		{
			static_assert(std::is_base_of<Rendering::RenderCommand, T>());

			void* pCommand = AllocateCommandObj(sizeof(T));
			T* pCommandPtr = (T*)pCommand;
			
			return MakeShared(pCommandPtr);
		}

		template<typename T>
		inline void PushRenderCommand(SharedPtr<T> command) 
		{
			static_assert(std::is_base_of<Rendering::RenderCommand, T>());
			Rendering::RenderCommand* pCommand = dynamic_cast<Rendering::RenderCommand>(command.get());
			m_CurrentFrameCommands.push_back(pCommand);
		}

		void ClearRenderCommands();

	private:
		void* AllocateCommandObj(size_t size)
		{
			return m_CommandPoolAllocator->Allocate(size);
		}

	private:
		RkPtr<Rocket::RkRendererManager> m_RenderManager;

		uint64 frameIndex;
		std::vector<Rendering::RenderCommand*> m_CurrentFrameCommands;

		// Would be nice to make a pool here, but a linear will have to do as our objects may change size (depending on what kind of command they are).
		Memory::LinearAllocator* m_CommandPoolAllocator;
	};
}