#pragma once

#include "core/CoreTypes.h"
#include "core/object/Object.h"
#include "core/object/ObjectManager.h"


#define RK_OBJECT_TYPE_OBJECTFLAGS_DEF()			\
static uint32 GetObjectFlags() {							\
		return (uint32)RkObjectFlags::None;					\
}

#define RK_OBJECT_TYPE_OBJECTFLAGS(ObjectFlags)				\
static uint32 GetObjectFlags() {							\
		return (uint32)(ObjectFlags);						\
}

#define RK_OBJECT_TYPE_INSTCOUNT(ObjectFlags)				\
static uint32 GetInstanceCount()							\
{															\
	const rkstring& typeName = GetTypeName();				\
	return gObjectManager->GetInstanceCount(typeName);		\
}							

#define RK_OBJECT_TYPE_NAME()								\
static rkstring GetTypeName() {								\
		const rkstring fileName = __FILE__;					\
		return fileName;									\
}

#define RK_OBJECT_BODY_NO_FLAGS()				\
RK_OBJECT_TYPE_OBJECTFLAGS_DEF()				\
RK_OBJECT_TYPE_INSTCOUNT()						\
RK_OBJECT_TYPE_NAME()							

#define RK_OBJECT_BODY_WITH_FLAGS(ObjectFlags)	\
RK_OBJECT_TYPE_OBJECTFLAGS(ObjectFlags)			\
RK_OBJECT_TYPE_INSTCOUNT()						\
RK_OBJECT_TYPE_NAME()							

#define RK_MACRO_STRIP(x,A,FUNC, ...)  FUNC

#define RK_OBJECT_BODY(...)				public: RK_MACRO_STRIP(,##__VA_ARGS__,\
														RK_OBJECT_BODY_WITH_FLAGS(__VA_ARGS__),\
														RK_OBJECT_BODY_NO_FLAGS(__VA_ARGS__)\
														) private:


template <typename TObjectType>
static TObjectType* CreateObject(Rocket::RkObject* parentObject, const rkstring& name)
{
	RK_ASSERT(Rocket::gObjectManager != nullptr);
	return Rocket::gObjectManager->NewObject<TObjectType>(parentObject, name);
}

template <typename TObjectType>
static TObjectType* CreateObject(Rocket::RkObject* parentObject)
{
	int32 instanceCount = TObjectType::GetInstanceCount();
	return CreateObject<TObjectType>(parentObject, TObjectType::GetTypeName() + "_0");
}