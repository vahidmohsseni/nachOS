

#ifndef THREADS_SJFSCHEDULER_H_
#define THREADS_SJFSCHEDULER_H_

#include "scheduler.h"
#include "system.h"

class SJFScheduler:public Scheduler {
public:
	SJFScheduler();
	virtual ~SJFScheduler();
	void ReadyToRun(Thread* thread);
	Thread* FindNextToRun();
	void Run(Thread* nextThread);
private:
	List *SJFreadyList;
};

#endif /* THREADS_SJFSCHEDULER_H_ */
