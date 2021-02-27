#include "EngineSubsystem.h"

#include "runtime/Engine.h"

Rocket::EngineSubsystem::EngineSubsystem()
	: m_Initialized(false), m_Shutdown(false)
{}

void Rocket::EngineSubsystem::ResetStateFlags()
{	
	m_Initialized = false;
	m_Shutdown = false;
}

void Rocket::EngineSubsystem::SetIsInitialized(bool isInitialized)
{
	m_Initialized = isInitialized;
}

void Rocket::EngineSubsystem::SetIsShutdown(bool isShutdown)
{
	m_Shutdown = isShutdown;
}
