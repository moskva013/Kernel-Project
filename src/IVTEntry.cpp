/*
 * IVTEntry.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "dos.h"

IVTEntry* IVTEntry::IVT[256];

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt newRoutine){
	lock;
	this->ivtNo=ivtNo;
	myKernelEv = 0;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(ivtNo);
	setvect(ivtNo, newRoutine);
#endif

	IVT[ivtNo] = this;
	unlock;
}

IVTEntry::~IVTEntry(){
	lock;
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, oldRoutine);
#endif
	unlock;
}

void IVTEntry::signal(){
	lock;
	if(myKernelEv){
	myKernelEv->signal();
	}
	unlock;
}

void IVTEntry::callOldInt(){
	lock;
	if(oldRoutine){
		(*oldRoutine)();
	}
	unlock;
}
