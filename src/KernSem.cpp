/*
 * KernSem.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#include "KernSem.h"
#include "timelist.h"
#include "SCHEDULE.H"

extern int lockFlag;

TimeList* KernelSem::timelist= new TimeList();

KernelSem::KernelSem(Semaphore* sem, int init){
	blockOnSem = new List();
	this->mySem = sem;
	this->value = init;
}

KernelSem::~KernelSem(){

	//blokiraniNaSem ti je pokazivac samo da znas

	//kaze uki da ovde prvo iz ove listi izbacimo sve niti pa tek onda da obrisemo sem
	if(blockOnSem->sizeList>0){
		blockOnSem->emptyList();
	}
	delete blockOnSem;
}

int KernelSem::wait(Time n){

	if(--value<0){

		PCB::running->blocked=1;
		PCB::running->ready=0;
		if(n>0){
			PCB::running->leftTimeBlocked=n;
			timelist->addElem(PCB::running, this);
		}
		blockOnSem->addElem(PCB::running);
		dispatch();
		//ovde sam odradio za povratnu vrednost pazi u listi da postavis dobro flag
		//tamo gde ga budes odblokirao

		if(PCB::running->flagReturnValueSemWait){
			PCB::running->flagReturnValueSemWait=0;
			return 0;
		}
		return 1;
	}
	return 1;
}


int KernelSem::signal(int n){
	int ret;
	if(n<0){
		ret = n;
		return ret;
	}

	if(n==0) {
		ret = 0;
		if(value++<0){
			//u sustini ovde je dovljno samo da update list
			PCB* tmp = blockOnSem->getFirstElem();
			if(tmp){
				tmp->ready=1;
				tmp->blocked=0;
				tmp->leftTimeBlocked=0;
				tmp->flagReturnValueSemWait=0;
				timelist->removeElem(tmp);
				Scheduler::put(tmp);
			}
		}

	}
	else{
		if(n>blockOnSem->sizeList){
			ret = blockOnSem->sizeList;
		}else{
			ret = n;
		}
		value=value+n;
		for(int i=0; i<ret; i++){
			PCB* tmp = blockOnSem->getFirstElem();
			tmp->blocked=0;
			tmp->ready=1;
			tmp->leftTimeBlocked=0;
			tmp->flagReturnValueSemWait=0;
			timelist->removeElem(tmp);
			Scheduler::put(tmp);
		}

	}

	return ret;
}

int KernelSem::getValue(){
	return value;
}
