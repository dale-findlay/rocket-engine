#pragma once

#include "core/CoreMinimal.h"
#include <vector>

#include "runtime/core/Entity.h"

namespace Rocket
{
	struct Scene 
	{
		rkstring name;
		std::vector<SharedPtr<Entity>> entities;
	};
}