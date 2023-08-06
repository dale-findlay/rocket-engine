#pragma once
#include "core/CoreTypes.h"

namespace Rocket
{
	enum class RkObjectFlags : uint32
	{
		None = 0x0,				//The object has no special properties.
		Abstract = 0x40			//The object is abstract and should not be constructed with NewObject.
	};

	enum class RkCreateObjectFlags : uint32
	{};

	class RkObject
	{
		friend class ObjectManager;
		template <typename> friend class RkPtr;

	public:
		// Destroy this object.
		void Destroy();

	private:		
		// the object has been forcefully destroyed, and it's waiting to be cleaned up by object manager.
		bool IsPendingCleanup() const;

		void SetParent(const RkObject* newParent);
		void SetName(const rkstring& newName);

		// Increase the refernce count of this object.
		void IncrementReferenceCount();

		// Decrease the reference count of this object.
		void DecrementReferenceCount();

	private:
		bool m_IsPendingCleanup;
		const RkObject* m_Parent;
		uint32 m_ReferenceCount;
		rkstring m_Name;
	};
}