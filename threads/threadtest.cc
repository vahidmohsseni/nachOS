// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"


// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void SimpleThread(int which)
{
    int num,j=0;

    // delay(2000);
    for (num = 0; num < 10; num++) {
        for (long int i=0;i<2000000;i++){j++;}
        printf("*** simpleThread thread %d looped %d times \n ", which, num);

        currentThread->Yield();
    }
    //printf("*** thread %d looped %d times , time =%d\n ", which, num,currentThread->finishTime);
}
void SimpleThread1(int which)
{
    int num,j=0;

    // delay(3000);
    for (num = 0; num < 10; num++) {
        for (long int i=0;i<3000000;i++){j++;}
        printf("*** simpleThread1 thread %d looped %d times \n ", which, num);

        currentThread->Yield();
    }
    //printf("*** thread %d looped %d times , time =%d\n ", which, num,currentThread->finishTime);
}

void SimpleThread2(int which)
{
    int num,j=0;

    // delay(4000);
    for (num = 0; num < 10; num++) {
        for (long int i=0;i<4000000;i++){j++;}
        printf("*** simpleThread2 thread %d looped %d times\n ", which, num);

        currentThread->Yield();
    }
    //printf("*** thread %d looped %d times , time =%d\n ", which, num,currentThread->finishTime);
}
void SimpleThread3(int which)
{
    int num,j=0;
    // delay(5000);
    for (num = 0; num < 10; num++) {
        for (long int i=0;i<5000000;i++){j++;}
        printf("*** simpleThread3 thread %d looped %d times\n ", which, num);
        currentThread->Yield();
    }
    //printf("*** thread %d looped %d times , time =%d\n ", which, num,currentThread->finishTime);
}
//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void PQThreadTest()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t1 = new Thread("forked thread");
    Thread *t2 = new Thread("forked thread");
    Thread *t3 = new Thread("forked thread");
    t1->priority=1;
    t2->priority=2;
    t3->priority=3;
    currentThread->priority=0;
    t1->Fork(SimpleThread, 1);
    t2->Fork(SimpleThread, 2);
    t3->Fork(SimpleThread, 3);
    SimpleThread(0);
}

void SJFThreadTest()
{
	DEBUG('t', "Entering ThreadTest1");
	Thread *t1 = new Thread("1forked thread");
	Thread *t2 = new Thread("2forked thread");
	Thread *t3 = new Thread("3forked thread");
	struct timeval tv;
	gettimeofday(&tv,NULL);
	unsigned long long time_in_micros = 1000000ll * tv.tv_sec + tv.tv_usec;
	currentThread->startTime=time_in_micros;

	t1->Fork(SimpleThread1, 1);
	t2->Fork(SimpleThread2, 2);
	t3->Fork(SimpleThread3, 3);
	SimpleThread(0);
}
//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	//PQThreadTest();
    SJFThreadTest();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}

