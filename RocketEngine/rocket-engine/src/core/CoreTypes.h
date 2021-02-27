#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <assert.h> 

typedef std::string			rkstring;

typedef unsigned long long	uint64;
typedef signed long long	int64;

typedef unsigned int		uint32;
typedef signed int			int32;

typedef unsigned char		uint8;
typedef signed char			int8;

typedef float				float32;
typedef double				float64;
typedef char				byte;

#define FORCEINLINE			__forceinline

#define SharedPtr			std::shared_ptr
#define MakeShared			std::make_shared

#define ROCKETASSERT(condition)	\
if(!(condition)) \
	__debugbreak();