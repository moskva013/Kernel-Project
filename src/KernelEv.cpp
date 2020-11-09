/*
 * KernelEv.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */


#include "KernelEv.h"
#include "SCHEDULE.H"
#include "IVTEntry.h"

KernelEv::KernelEv(IVTNo ivtNo){
	ownerPCB = PCB::running;
	this->ivtNo = ivtNo;
	binaryValue = 0;
	blockedPCB = 0;
	myIVTEntry = IVTEntry::IVT[ivtNo];
	myIVTEntry->myKernelEv = this;
}

KernelEv::~KernelEv(){
	if(blockedPCB){
		blockedPCB->blocked = 0;
		blockedPCB->ready = 1;
		Scheduler::put(blockedPCB);
		blockedPCB = 0;
	}
	myIVTEntry = 0;
	ownerPCB = 0;
}

void KernelEv::wait(){
	if(PCB::running == ownerPCB){
		if(binaryValue == 1){
			binaryValue = 0;
		}else{
			PCB::running->blocked = 1;
			PCB::running->ready = 0;
			blockedPCB = PCB::running;
			dispatch();
		}
	}
}

void KernelEv::signal(){
	if(blockedPCB == 0){
		binaryValue = 1;
	}else{
		//ovde treba da odblokiram nit i postavim pokazivac na 0 kaze ziza
		blockedPCB->blocked = 0;
		blockedPCB->ready = 1;
		Scheduler::put(blockedPCB);
		blockedPCB = 0;
	}
	dispatch();
}
