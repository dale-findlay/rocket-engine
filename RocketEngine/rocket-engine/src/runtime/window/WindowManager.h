#pragma once

#include "core/EngineSubsystem.h"
#include "runtime/window/windows/Window.h"

namespace Rocket
{
	class WindowManager : public EngineSubsystem
	{
	public:
		WindowManager();

		// Inherited via EngineSubsystem
		virtual bool Init() override;
		virtual void Shutdown() override;

		void PreFrameUpdate();
		void PostFrameUpdate();

		FORCEINLINE Window* GetWindow() 
		{
			return m_window;
		}

	private:
		Window* m_window;
	};
}