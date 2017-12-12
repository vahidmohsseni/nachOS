
#ifndef MLQSCHEDULER_H
#define MLQSCHEDULER_H


#include "scheduler.h"
#include "system.h"

class MLQScheduler:public Scheduler {
public:
	MLQScheduler();
	virtual ~MLQScheduler();
	void ReadyToRun(Thread* thread);	// Thread can be dispatched.
	Thread* FindNextToRun();		// Dequeue first thread on the ready
	void Run(Thread* nextThread);
private:
    List *multilevelPQ;
    List *multilevelSJF;
};


#endif // MLQSCHEDULER_H
