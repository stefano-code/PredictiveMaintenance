#include "CriticalSectionLock.hpp"

CriticalSectionLock::CriticalSectionLock(SemaphoreBase* semaphore_)
{
	pSemaphore = semaphore_;
	pSemaphore->acquire();
}

CriticalSectionLock::~CriticalSectionLock()
{
	pSemaphore->release();
}


