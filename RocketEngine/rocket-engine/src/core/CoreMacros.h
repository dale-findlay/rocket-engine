#pragma once

#include <memory>
#include <assert.h> 
 
#define FORCEINLINE			__forceinline

#define SharedPtr			std::shared_ptr
#define MakeShared			std::make_shared

#define ROCKETASSERT(condition)	\
if(!(condition)) \
	__debugbreak();