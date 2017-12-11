// rrscheduler.h 
//	Data structures for the thread dispatcher and scheduler.
//	Primarily, the list of threads that are ready to run.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef RRSCHEDULER_H
#define RRSCHEDULER_H

#include "copyright.h"
#include "list.h"
#include "thread.h"
#include "scheduler.h"

// The following class defines the scheduler/dispatcher abstraction -- 
// the data structures and operations needed to keep track of which 
// thread is running, and which threads are ready but not running.

class RRScheduler : public Scheduler {
  public:
    RRScheduler();			// Initialize list of ready threads 
    ~RRScheduler();			// De-allocate ready list

    void ReadyToRun(Thread* thread);	// Thread can be dispatched.
    Thread* FindNextToRun();		// Dequeue first thread on the ready
};

#endif // RRSCHEDULER_H
