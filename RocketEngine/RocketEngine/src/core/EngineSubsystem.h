#pragma once

#include "core/CoreMinimal.h"
#include "core/CoreSubsystem.h"

namespace Rocket
{
	class RkEngineSubsystem : public RkObject, CoreSubsystem
	{
		RK_OBJECT_BODY()
	public:
		RkEngineSubsystem();

		virtual bool Init() = 0;
		virtual void Shutdown() = 0;

		bool IsInitialized() const {
			return m_Initialized;
		}

		bool IsShutdown() const {
			return m_Shutdown;
		}

	protected:
		void ResetStateFlags();

		//It's the responsibility of each system to manage how it's init and shutdown procedure is defined.
		void SetIsInitialized(bool isInitialized);
		void SetIsShutdown(bool isShutdown);

	private:		
		//Has this system been initialized.
		bool m_Initialized;
		//Has this system been shutdown.
		bool m_Shutdown;

	};
}
