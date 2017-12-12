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


//*********simple multiple producer_consumer problem using semaphors******************
#include "copyright.h"
#include <stdlib.h>
#include "system.h"
#include "synch.h"
#include <iostream>
#include <time.h>

#include "unistd.h"

using namespace std;

#define buffersize 100
#define numberOfProducers 8
#define numberOfConsumers 8
int  buffer[buffersize];
int counter=0;

Semaphore *full =new Semaphore("full", 0);
Semaphore *empty =new Semaphore("empty", buffersize);
Semaphore *mutex =new Semaphore("mutex", 1);//for critical region




// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// producerThread
//----------------------------------------------------------------------

void
producerThread(int which)
{
	srand(1);//time(NULL));
	cout<<"Producer starts:\n";

	while(1){
				
		int randomnumber;
		randomnumber = rand() % 50;//produce randomnumber to put into buffer
		
		empty->P();//down(empty)
		mutex->P();//down(mutex)
		buffer[counter]=randomnumber;
		cout<<"Producer puts\n";
		counter=counter + 1;
		mutex->V();//up(mutex)
		full->V();//up(full) 
			
	}
	
	cout<<"Producer finishes.\n";
}

//----------------------------------------------------------------------
// consumerThread
//----------------------------------------------------------------------

void
consumerThread(int which)
{

	cout<<"Consumer starts:\n";

	while(1){
		
		full->P();//down(full)
		mutex->P();//down(mutex)
		counter=counter-1;
		int consumeItem=buffer[counter];
		mutex->V();//up(mutex)
		empty->V();//up(empty)
		sleep(2);
		
		cout<<"Consumer consumed the consumeItem!\n";
			
	}
	
	cout<<"Consumer finishes.\n";
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//main.cc calls this function
//----------------------------------------------------------------------

void
ThreadTest()
{
	cout<<"ThreadTest starts:\n";
	
	Thread *producers[numberOfProducers];
	Thread *consumers[numberOfConsumers];

	for(int i=0; i<numberOfProducers; i++){
	
		producers[i] = new Thread("Producer");
		producers[i]->Fork(producerThread, i);	
		
		}
		
	for(int j=0; j<numberOfConsumers; j++){
		
		consumers[j] = new Thread("Consumer");
		consumers[j]->Fork(consumerThread, j);
		
		}
	
	cout<<"ThreadTest finishes\n";			
}

