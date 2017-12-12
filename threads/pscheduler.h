// scheduler.h 
//	Data structures for the thread dispatcher and scheduler.
//	Primarily, the list of threads that are ready to run.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef PSCHEDULER_H
#define PSCHEDULER_H

#include "copyright.h"
#include "list.h"
#include "thread.h"
#include "scheduler.h"
#include "system.h"


// The following class defines the scheduler/dispatcher abstraction -- 
// the data structures and operations needed to keep track of which 
// thread is running, and which threads are ready but not running.

class PScheduler : public Scheduler {
  public:
   // PScheduler();			// Initialize list of ready threads 
  //  ~PScheduler();			// De-allocate ready list

    void ReadyToRun(Thread* thread);	// Thread can be dispatched.
    Thread* FindNextToRun();		// Dequeue first thread on the ready
};

#endif // PSCHEDULER_H
