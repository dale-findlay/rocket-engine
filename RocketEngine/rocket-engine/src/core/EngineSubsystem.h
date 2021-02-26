#pragma once

#include "CoreTypes.h"

namespace Rocket
{

	class EngineSubsystem
	{
	public:
		virtual bool Init() = 0;
		virtual void Shutdown() = 0;

		FORCEINLINE bool IsInitialized() const {
			return m_Initialized;
		}

		FORCEINLINE bool IsShutdown() const {
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
