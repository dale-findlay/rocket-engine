#pragma once

#include "core/EngineSubsystem.h"
#include "runtime/window/windows/Window.h"

namespace Rocket
{
	class RkWindowManager : public RkEngineSubsystem
	{
		RK_OBJECT_BODY()
	public:		
		RkWindowManager();

		virtual bool Init() override;
		virtual void Shutdown() override;

		void PreFrameUpdate();
		void PostFrameUpdate();

		FORCEINLINE RkWindow* GetWindow() 
		{
			return m_window;
		}

	private:
		RkWindow* m_window;
	};
}