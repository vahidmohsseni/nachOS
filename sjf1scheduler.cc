#include "sjfscheduler.h"
#include "synch.h"
#include <time.h>

SJFScheduler::SJFScheduler() : Scheduler()
{

	lastTime = time(0);
}

SJFScheduler::~SJFScheduler()
{
}


void SJFScheduler::ReadyToRun(Thread* thread)
{

    DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());
    printf("thread %s is on ready list.\n", thread->getName());

    thread->setStatus(READY);
    readyList->Append((void *)thread);
}

//------------------------------------------------------------------------
// FindNextToRun
// here after updating the time, we make a temp list, and assign minTime
// to 999999, this number is for the first comparison that we make.
// after that each time the thread will be comapred to minTime and 
// if it is less than minTime, it will be assigned to minTime
// and then we Append the thread.
//-----------------------------------------------------------------------

Thread* SJFScheduler::FindNextToRun()
{
	UpdateTime();

    if ( readyList->IsEmpty() )
    	return NULL;
	
	List* tmp= new List;
	int minTime = 9999999 ;
	
	while(!readyList->IsEmpty())
	{
		Thread * t1 = (Thread* ) readyList->Remove();
		
		if(jobTimes[atoi(t1->getName())] < minTime)
			minTime = jobTimes[atoi(t1->getName())];
		
		tmp->Append(t1);
	}
	
	readyList = tmp;
	Thread *t2 =  (Thread *) readyList->Remove();
	
	 while (jobTimes[atoi(t2->getName())] > minTime
	 	)
	 {
	 	readyList->Append((void *)t2);
	 	t2 = (Thread *) readyList->Remove();
	 }
	return t2;
}


void SJFScheduler::UpdateTime()
{
    char *name = currentThread->getName();
    int currentTime = time(0);
    jobTimes[atoi(name)] = currentTime - lastTime;
    lastTime = time(0);

}

int SJFScheduler::FindShortest()
{
    int index = 1;
    int min = jobTimes[1];
    for (int i = 2; i < 11; i++)
        if (jobTimes[i] < min)
        {
            min = jobTimes[i];
            index = i;
        }
    return index;
}

Thread* SJFScheduler::GetShortest()
{

	List* tmp;
	int minTime = 9999999 ;

	while(!readyList->IsEmpty())
	{
		Thread * t1 = (Thread* ) readyList->Remove();
		
		if(jobTimes[atoi(t1->getName())] < minTime)
			minTime = jobTimes[atoi(t1->getName())];
		tmp->Append( t1 );
	}

	readyList = tmp;
	Thread *t2 =  (Thread *) readyList->Remove();

	 while (jobTimes[atoi(t2->getName())] > minTime
	 	){

	   readyList->Append(t2);
	   t2 = (Thread *) readyList->Remove();
	}
	return t2;
}
