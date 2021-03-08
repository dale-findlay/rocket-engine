#pragma once
#include "core/CoreMinimal.h"

namespace Rocket 
{
	namespace AssetManagement 
	{
		/**
		 * Asset Spec
		 */
		typedef struct
		{
			int fileVersion;
			int fileType;
		} RkAssetSpecBlock;

		/**
		 * Referenced Asset Paths.
		 */
		typedef struct
		{
			uint32		blockSize;
			rkwchar*	blockChars;
		} RkReferencedAssetPathsBlock;

		/**
		 * Source File Info.
		 */
		typedef struct
		{
			uint32			originalFileLengthBytes;
			rkwchar*		originalFileBytes;
		} RkSourceFileInfoBlock;

		/**
		 * Asset Data Block
		 */
		typedef struct
		{
			uint32			assetDataLengthBytes;
			byte*			assetDataBytes;
		} RkAssetDataBlock;
	}
}