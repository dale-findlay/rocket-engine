#include "ForwardRenderer.h"
#include "runtime/Engine.h"
#include "GLFW/glfw3.h"
#include "runtime/window/WindowManager.h"

Rocket::Rendering::ForwardRenderer::ForwardRenderer()
    : Renderer()
{}

bool Rocket::Rendering::ForwardRenderer::Init()
{
    Renderer::Init();
 
    return true;
}

void Rocket::Rendering::ForwardRenderer::Shutdown()
{
    Renderer::Shutdown();
}

void Rocket::Rendering::ForwardRenderer::DrawFrame()
{

    Renderer::DrawFrame();
}

