#ifndef CRITICALSECTIONLOCK_HPP
#define	CRITICALSECTIONLOCK_HPP

#include "Semaphore.hpp"

class CriticalSectionLock
{
public:
	CriticalSectionLock(SemaphoreBase* semaphore_);
	virtual ~CriticalSectionLock();
private:
	SemaphoreBase* pSemaphore;
};

#endif	/* CRITICALSECTIONLOCK_HPP */

