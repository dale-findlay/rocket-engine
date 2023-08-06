#pragma once

#include <memory>
#include <iostream>
#include <assert.h> 
 
#define FORCEINLINE			__forceinline

#define SharedPtr			std::shared_ptr
#define MakeShared			std::make_shared

#define RK_LOG(Verbosity, Message) \
std::cout << "Rocket: " << Message << std::endl; \

#define RK_ASSERT(condition)	\
if(!(condition)) \
	__debugbreak();