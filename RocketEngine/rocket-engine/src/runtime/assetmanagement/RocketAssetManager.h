#pragma once

#include "core/EngineSubsystem.h"
#include "runtime/memory/allocators/MemoryAllocator.h"

namespace Rocket {

	class RocketAssetManager : public EngineSubsystem
	{
	public:
		// Inherited via EngineSubsystem
		virtual bool Init() override;
		virtual void Shutdown() override;

		FORCEINLINE Memory::MemoryAllocator* GetMemoryAllocator() {
			return m_Allocator;
		}

		class RocketAsset* LoadRocketAsset(const rkstring& path);

	private:
		Memory::MemoryAllocator* m_Allocator;
		RocketAssetFactory* m_Factory;
	};

}