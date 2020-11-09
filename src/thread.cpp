/*
 * thread.cpp
 *
 *  Created on: Sep 4, 2020
 *      Author: OS1
 */


#include "thread.h"
#include "Pcb.h"
#include "SCHEDULE.H"
#include "iostream.h"


extern lockFlag;

Thread::Thread(StackSize stackSize, Time timeSlice){

	/*
	lockFlag=0;
	cout<<"Usao u konstruktor Thread"<<endl;
	lockFlag=1;
	 */
	myPCB = new PCB(stackSize, timeSlice, this);
	allThreads->addElem(myPCB);
}


void Thread::start(){
		/*lockFlag=0;
		cout<<"Pozvala se start metoda"<<endl;
		lockFlag=1;
		*/

	if(this->myPCB->created && this->myPCB->ready == 0){ //dodao sam ono sto je ziza rekao da ista nit ne moze vise puta da poziva metodu start
		this->myPCB->ready=1;
		Scheduler::put(this->myPCB);
	}

}

ID Thread::getId(){
	return this->myPCB->myId;
}

ID Thread::getRunningId(){
	return PCB::running->myId;
}

Thread* Thread::getThreadById(ID id){
	PCB* help = allThreads->searchInList(id);
	Thread* ret = help->myThread;
	return ret;
}

void Thread::waitToComplete(){

		/*lockFlag=0;
		cout<<"Pozvala se metoda waitToComplete"<<endl;
		lockFlag=1;
		 */

	if(PCB::running->finished==0 && myPCB->finished==0){
		lockFlag=0;
		PCB::running->blocked = 1;
		myPCB->blockedThreads->addElem((PCB*)PCB::running);
		lockFlag=1;
		dispatch();
	}
	/*
	lockFlag=0;
	cout<<"wait to complete"<<endl;
	lockFlag=1;
	*/

}

PCB* Thread::getPCB(){
	return myPCB;
}

Thread::~Thread(){
	waitToComplete();
	if(myPCB) delete myPCB;
	/*
	lockFlag=0;
	cout<<"Obrisala se nit"<<endl;
	lockFlag=1;
	*/
}

void Thread::setFinished(){
	myPCB->finished = 1;
}
