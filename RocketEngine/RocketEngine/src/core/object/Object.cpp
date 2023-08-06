#include "Object.h"
#include "core/CoreMacros.h"

void Rocket::RkObject::Destroy()
{
	// next time the garbage collector runs, it will pick this object up to be cleaned up.
	m_IsPendingCleanup = true;
}

bool Rocket::RkObject::IsPendingCleanup() const
{
	return m_IsPendingCleanup;
}

void Rocket::RkObject::SetParent(const RkObject* newParent)
{
	m_Parent = newParent;
}

void Rocket::RkObject::SetName(const rkstring& name)
{
	m_Name = name;
}

void Rocket::RkObject::IncrementReferenceCount()
{
	m_ReferenceCount++;
}

void Rocket::RkObject::DecrementReferenceCount()
{
	RK_ASSERT(m_ReferenceCount - 1 > 0);

	m_ReferenceCount--;
}
