#pragma once
#include "core/CoreMinimal.h"
#include <vector>

namespace Rocket {

	enum class Rocj

	typedef struct
	{
		int fileVersion;
		int fileType;
		std::vector<rkwstring>	referencedAssetPaths;
		rkwstring originalFilePath;
	} RkAsset;

	class RocketAsset 
	{
		friend class RocketAssetManager;
	protected:
		RocketAsset();
		~RocketAsset();
		
	protected:
		RkAsset	m_Asset;
	};
}