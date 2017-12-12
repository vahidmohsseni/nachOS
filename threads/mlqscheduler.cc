
#include "mlqscheduler.h"
#include <sys/time.h>

MLQScheduler::MLQScheduler() {
	multilevelSJF = new List;
	multilevelPQ = new List;
}

MLQScheduler::~MLQScheduler() {
	delete multilevelSJF;
	delete multilevelPQ;
}

Thread* MLQScheduler::FindNextToRun(){
    return multilevelSJF->IsEmpty() ? (Thread*)multilevelPQ->SortedRemove(NULL) : (Thread*)multilevelSJF->SortedRemove(NULL);
}

void MLQScheduler::ReadyToRun(Thread* thread){
	DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());
	thread->setStatus(READY);
	if (thread->priority==-1)
		multilevelSJF->SortedInsert((void*) thread,thread->rettimejobdone());
	else
		multilevelPQ->SortedInsert((void*) thread,thread->priority);
}

void MLQScheduler::Run(Thread* nextThread){
	Thread *oldThread = currentThread;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	unsigned long long time_in_micros = 1000000ll * tv.tv_sec + tv.tv_usec;
	oldThread->finishTime=time_in_micros;
	oldThread->settimejobdone(oldThread->finishTime-oldThread->startTime);

	#ifdef USER_PROGRAM			// ignore until running user programs
	    if (currentThread->space != NULL) {	// if this thread is a user program,
	        currentThread->SaveUserState(); // save the user's CPU registers
		currentThread->space->SaveState();
	    }
	#endif

	oldThread->CheckOverflow();

	currentThread = nextThread;
	currentThread->setStatus(RUNNING);

	DEBUG('t', "Switching from thread \"%s\" to thread \"%s\"\n",
	  oldThread->getName(), nextThread->getName());

	SWITCH(oldThread, nextThread);
	DEBUG('t', "Now in thread \"%s\"\n", currentThread->getName());
	struct timeval tvv;
	gettimeofday(&tvv,NULL);
	unsigned long long time_in_micross = 1000000ll * tvv.tv_sec + tvv.tv_usec;
	currentThread->startTime=time_in_micross;
	// If the old thread gave up the processor because it was finishing,
	// we need to delete its carcass.  Note we cannot delete the thread
	// before now (for example, in Thread::Finish()), because up to this
	// point, we were still running on the old thread's stack!
	if (threadToBeDestroyed != NULL) {
		delete threadToBeDestroyed;
		threadToBeDestroyed = NULL;
	}

	#ifdef USER_PROGRAM
	    if (currentThread->space != NULL) {		// if there is an address space
	        currentThread->RestoreUserState();     // to restore, do it.
		currentThread->space->RestoreState();
	    }
	#endif
}
