#include "ForwardRenderer.h"
#include "runtime/Engine.h"
#include "GLFW/glfw3.h"

Rocket::Rendering::ForwardRenderer::ForwardRenderer()
    : Renderer()
{}

bool Rocket::Rendering::ForwardRenderer::Init()
{
    Renderer::Init();
    
    gEngine->GetWindowManager()->GetWindow()->MakeContextCurrent();

    glClearColor(0, 0, 0, 1);    
    return true;
}

void Rocket::Rendering::ForwardRenderer::Shutdown()
{
    Renderer::Shutdown();
}

void Rocket::Rendering::ForwardRenderer::DrawFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Renderer::DrawFrame();
}

