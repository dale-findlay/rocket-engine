#include "EngineSubsystem.h"

#include "runtime/Engine.h"

Rocket::RkEngineSubsystem::RkEngineSubsystem()
	: m_Initialized(false), m_Shutdown(false)
{}

void Rocket::RkEngineSubsystem::ResetStateFlags()
{	
	m_Initialized = false;
	m_Shutdown = false;
}

void Rocket::RkEngineSubsystem::SetIsInitialized(bool isInitialized)
{
	m_Initialized = isInitialized;
}

void Rocket::RkEngineSubsystem::SetIsShutdown(bool isShutdown)
{
	m_Shutdown = isShutdown;
}
