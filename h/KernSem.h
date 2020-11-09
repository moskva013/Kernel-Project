/*
 * KernSem.h
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include "semaphor.h"
#include "list.h"

class TimeList;

class KernelSem{

public:
	static TimeList* timelist;

	List* blockOnSem;

	KernelSem(Semaphore* sem, int init);
	~KernelSem();

	int wait(Time n);
	int signal(int n);
	int getValue();

private:
	volatile int value;
	Semaphore* mySem;
};



#endif /* KERNSEM_H_ */
