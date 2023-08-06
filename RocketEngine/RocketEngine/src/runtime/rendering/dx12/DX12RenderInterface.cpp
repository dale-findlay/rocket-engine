#include "DX12RenderInterface.h"
#include "DX12RenderSurface.h"
#include "runtime/Engine.h"

bool Rocket::DX12RenderInterface::Initialize()
{
    // create dxgi factor
    // enum adapters
    // create device

    return false;
}

void Rocket::DX12RenderInterface::Shutdown()
{
}

Rocket::RkRenderSurface* Rocket::DX12RenderInterface::ConstructRenderSurface()
{
    //use the renderer manager as the parent.
    RkRendererManager* rendererManager = gEngine->GetSubsystem<Rocket::RkRendererManager>();
    RK_ASSERT(rendererManager)

    RkDX12RenderSurface* newRenderSurface = CreateObject<RkDX12RenderSurface>(rendererManager);

    return nullptr;
}
