#pragma once

#include "core/CoreMinimal.h"

namespace Rocket
{
	namespace Memory
	{
		/**
		 * Simpler pointer math class to help the allocator implementations.
		 */
		class AllocatorUtility
		{
			public:
			/**
			 * n-byte aligns any given memory address for any given alignment.
			 */
			inline static void* AlignForward(void* p, uint8 alignment)
			{
				uint64 maskBytes = static_cast<uint64>(alignment - 1);
				uint64 complementMaskBytes = ~(maskBytes);

				uint64 pMasked = reinterpret_cast<uint64>(p) + maskBytes; //mask off the log2(n) least significant bits.

				return (void*)(pMasked & complementMaskBytes);
			}

			/**
			 * Calculates the number of bytes needed to align this pointer.
			 */
			inline static uint8 CalculateAdjustment(const void* p, uint8 alignment)
			{
				uint64 maskBytes = static_cast<uint64>(alignment - 1);
				uint64 pBytesOut = reinterpret_cast<uint64>(p) & maskBytes;

				uint8 adjustment = (uint8)((uint64)alignment - pBytesOut);

				//Check if p is already aligned.
				if (adjustment == alignment)
				{
					return 0;
				}

				return adjustment;
			}

			/**
			 * Calculate the adjustment to offset the memory overhead of the allocators using headers.
			 */
			inline static uint8 CalculateAlignForwardHeaderAdjustment(const void* p, uint8 alignment, uint8 headerSize)
			{
				uint8 adjustment = CalculateAdjustment(p, alignment);

				//Check if we have enough space
				if (adjustment < headerSize)
				{
					headerSize -= adjustment;
					adjustment += alignment * (headerSize / alignment); //Scale the adjustment to fit the header size.

					if (headerSize % alignment > 0)
					{
						adjustment += alignment;
					}
				}

				return adjustment;
			}
		};
	}
}