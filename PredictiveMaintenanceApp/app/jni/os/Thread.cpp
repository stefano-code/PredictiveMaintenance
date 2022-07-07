#include "Thread.hpp"
#include "debug\Logger.hpp"
#include <sys\types.h>
#include <unistd.h>


Thread::~Thread()
{
}

Thread::Thread(uint32_t priority, const char* name)
{
    startSem.acquire();
    pthread_create(&handle, NULL, Wrapper, (void*)this);
    pthread_setname_np( handle, name);
}

void Thread::Start()
{
    pid_t id = gettid();
    Log.Append( "releasing tid %d", id);
    Log.EndLine();
    startSem.release();
}

void* Thread::Wrapper(void *object)
{
    Thread* thread = reinterpret_cast<Thread *> (object);
    thread->startSem.acquire();
    thread->Run();

    return NULL;
}

void Thread:: Sleep(unsigned int millisecondWait)
{
    usleep(millisecondWait*1000u);
}




