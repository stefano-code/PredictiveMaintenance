
#ifndef MDB__THREAD_HPP
#define MDB__THREAD_HPP

#include <cstdint>
#include <pthread.h>
#include "Semaphore.hpp"

class Thread
{
public:
	Thread(uint32_t priority, const char* name);
	virtual ~Thread();
	void Start();
	static void Sleep(unsigned int millisecondWait);
protected :
	virtual void Run() = 0;
private:
	static void* Wrapper(void *object);

	Thread(const Thread& other);
	Thread & operator=(const Thread& other);

	pthread_t handle;
	SemaphoreBase startSem;
};


#endif // MDB__THREAD_HPP
