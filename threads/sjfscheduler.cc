

#include "sjfscheduler.h"
#include "ctime"
#include <sys/time.h>


SJFScheduler::SJFScheduler() {
	SJFreadyList = new List;
}

SJFScheduler::~SJFScheduler() {
	delete SJFreadyList;
}

Thread* SJFScheduler::FindNextToRun(){
	Thread* t=(Thread*)SJFreadyList->SortedRemove(NULL); // get the thread which its job-done-time is shorter than others
	return t;
}

void SJFScheduler::ReadyToRun(Thread* thread){
	DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());
	thread->setStatus(READY);
	SJFreadyList->SortedInsert((void*) thread,thread->rettimejobdone()); // insert a thread in readylist
}


// this method is same as Run method in scheduler class
// just added some variables to get a thread time when its job is done
void SJFScheduler::Run(Thread* nextThread){
	Thread *oldThread = currentThread;

	struct timeval tv;
	gettimeofday(&tv,NULL);
	unsigned long long time_in_micros = 1000000ll * tv.tv_sec + tv.tv_usec;

	oldThread->finishTime=time_in_micros;
	oldThread->settimejobdone(oldThread->finishTime-oldThread->startTime); // get done time and set it for next time run

	#ifdef USER_PROGRAM			// ignore until running user programs
	    if (currentThread->space != NULL) {	// if this thread is a user program,
	        currentThread->SaveUserState(); // save the user's CPU registers
		currentThread->space->SaveState();
	    }
	#endif

	    oldThread->CheckOverflow();		    // check if the old thread
						    				// had an undetected stack overflow

	    currentThread = nextThread;		    // switch to the next thread
	    currentThread->setStatus(RUNNING);  // nextThread is now running
	    struct timeval tvv;
		gettimeofday(&tvv,NULL);
		unsigned long long time_in_micross = 1000000ll * tvv.tv_sec + tvv.tv_usec;
		currentThread->startTime=time_in_micross;
	    DEBUG('t', "Switching from thread \"%s\" to thread \"%s\"\n",
		  oldThread->getName(), nextThread->getName());

	    // This is a machine-dependent assembly language routine defined
	    // in switch.s.  You may have to think
	    // a bit to figure out what happens after this, both from the point
	    // of view of the thread and from the perspective of the "outside world".

	    SWITCH(oldThread, nextThread);


	    DEBUG('t', "Now in thread \"%s\"\n", currentThread->getName());

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
