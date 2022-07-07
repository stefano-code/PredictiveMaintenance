
#include "Semaphore.hpp"



SemaphoreBase::SemaphoreBase()
{
handle =  PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
}

SemaphoreBase::~SemaphoreBase()
{
	pthread_mutex_destroy(&handle);
}

bool SemaphoreBase::acquire()
{
	return pthread_mutex_lock( &handle ) == 0 ;
}

bool SemaphoreBase::acquire(int timeoutMs)
{
	struct timespec timeoutTime;
	clock_gettime(CLOCK_REALTIME, &timeoutTime);
	timeoutTime.tv_sec += 60;
	return  pthread_mutex_timedlock(&handle, &timeoutTime) == 0;
}

void SemaphoreBase::release()
{
	pthread_mutex_unlock( &handle );
}









