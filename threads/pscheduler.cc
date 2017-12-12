#include "pscheduler.h"
/*
PScheduler::PScheduler() : Scheduler()
{
}

PScheduler::~PScheduler()
{
}
*/

void PScheduler::ReadyToRun(Thread* thread)
{
	 DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());
    
    //***************************************************************************************************
	//thread->priority = getPriority();
    thread->setStatus(READY);
  // readyList->Append((void *)thread);
    readyList->SortedInsert((void *)thread , thread->priority);//*************************
    //*************************************************************
   /* ListElement *le=readyList->first;
    while(le != NULL){
		//sortedReadyList->SortedInsert((void *)readyList->first , thread->priority);
		sortedReadyList->SortedInsert((void *)le , thread->priority);
		le=le->next;
*/
}

Thread* PScheduler::FindNextToRun()
{
	    return (Thread *)readyList->Remove();
    //*********************************************8
    	/*List *list = sortedReadyList;
		return (Thread *)sortedReadyList->Remove();*/
}

