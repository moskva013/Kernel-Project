/*
 * semaphor.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */


#include "semaphor.h"
#include "KernSem.h"

extern int lockFlag;


Semaphore::Semaphore(int init){
	lockFlag=0;
	myImpl = new KernelSem(this, init);
	lockFlag=1;
}

Semaphore::~Semaphore(){
	lockFlag=0;
	delete myImpl;
	lockFlag=1;
}

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

int Semaphore::signal(int n){
	return myImpl->signal(n);
}

int Semaphore::val() const{
	return myImpl->getValue();
}
