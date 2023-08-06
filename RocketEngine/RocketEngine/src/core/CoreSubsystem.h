#pragma once

namespace Rocket
{
	class CoreSubsystem
	{
	public:
		virtual bool Init() = 0;
		virtual void Shutdown() = 0;
	};
}