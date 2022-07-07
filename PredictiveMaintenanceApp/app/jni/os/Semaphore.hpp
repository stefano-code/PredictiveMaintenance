
#ifndef MDB__SEMAPHORE_HPP
#define MDB__SEMAPHORE_HPP


#include <pthread.h>



class SemaphoreBase
{
public:
	SemaphoreBase();
	~SemaphoreBase();
	bool acquire();
	bool acquire(int timeoutMs);
	void release();
protected:
	pthread_mutex_t handle;

private:
	SemaphoreBase(const SemaphoreBase&);
	SemaphoreBase &
			operator=(const SemaphoreBase&);
};



#endif // MDB__SEMAPHORE_HPP

