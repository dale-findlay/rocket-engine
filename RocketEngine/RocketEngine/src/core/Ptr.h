#pragma once

template<typename TObjectType>
class RkPtr
{
public:
	RkPtr() {}

	RkPtr(TObjectType* inPtr) 
		: m_Ptr(inPtr)
	{
		m_Ptr->IncrementReferenceCount();
	}

	~RkPtr()
	{
		m_Ptr->DecrementReferenceCount();
	}

	TObjectType* operator->() {
		return m_Ptr;
	}

private:
	TObjectType* m_Ptr;
};