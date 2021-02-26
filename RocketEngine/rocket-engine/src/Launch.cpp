
#include "runtime/Engine.h"

int main() 
{
	Rocket::Engine engine;

	if (!engine.Init())
	{
		return -1;
	}

	int32 returnCode = engine.Run();

	engine.Shutdown();

	return returnCode;
}