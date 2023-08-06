#include "DX12RenderSurface.h"
#include "runtime/Engine.h"
#include "runtime/window/windows/Win32Window.h"

bool Rocket::RkDX12RenderSurface::Initialize()
{
	RK_ASSERT(gEngine);
	RkWindowManager* windowManager = gEngine->GetSubsystem<RkWindowManager>();
	
	RK_ASSERT(windowManager);
	RkWindow* window = windowManager->GetWindow();

	Rocket::Windows::RkWin32Window* win32Window = dynamic_cast<Rocket::Windows::RkWin32Window*>(window);

	HWND hwnd = win32Window->GetHwnd();

	return true;
}
