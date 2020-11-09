/*
 * Pcb.cpp
 *
 *  Created on: Sep 5, 2020
 *      Author: OS1
 */



#include "Pcb.h"
#include <dos.h>
#include "List.h"
#include "SCHEDULE.H"
#include "iostream.h"

ID posId=0;
extern lockFlag;

List *allThreads = new List();
PCB* PCB::running=0;
PCB* PCB::startingThread=0;
Idle* PCB::idle = 0;


void PCB::wrapper(){
	if(PCB::running->myThread){
		PCB::running->myThread->run();
	}
	lockFlag=0;
	PCB::running->finished = 1;
	//uki reko: ovde trebas da prodjes kroz listu niti (koje cekaju da se ova nit zavrsi) i sve te niti vratis u scheduler
	PCB* cur;
	while(cur = PCB::running->blockedThreads->getFirstElem()){
		cur->blocked=0;
		cur->ready=1;
		Scheduler::put(cur);
	}//ako nesto ne bude valjalo mozda je zbog toga sto ti ovde baca null pointer exception!!!!!!!!!!!!
	lockFlag=1;
	dispatch();
}

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* thread){

		/*lockFlag=0;
		cout<<"Usao u konstruktor PCB"<<endl;
		lockFlag=1;
		*/
															//podesavanje da bude 64kb
	if(stackSize > 65536) this->myStackSize = 65534;
	else this->myStackSize = stackSize/sizeof(unsigned);
															//gimnastika za timeSlice ako je 0
	if(timeSlice == 0) endless = 1;
	else endless = 0;

	myTSlice = timeSlice;
	myThread = thread;

	stack = new unsigned[myStackSize];
	stack[myStackSize-1]= 0x200;

	#ifndef BCC_BLOCK_IGNORE
	stack[myStackSize-2] = FP_SEG(PCB::wrapper);
	stack[myStackSize-3] = FP_OFF(PCB::wrapper);

	this->sp = FP_OFF(stack+myStackSize-12);
	this->ss = FP_SEG(stack+myStackSize-12);
	this->bp = FP_OFF(stack+myStackSize-12); //isto sto i sp
	#endif
	finished = 0;
	created = 1;
	ready = 0;
	blocked = 0;
	myId = ++posId;
	this->blockedThreads = new List();


}


PCB::~PCB(){
	if(this->blockedThreads) delete blockedThreads;

	if(this->stack) delete stack;

	myThread = 0;
}

