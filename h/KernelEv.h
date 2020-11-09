/*
 * KernelEv.h
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "event.h"
#include "IVTEntry.h"
#include "PCB.h"

class IVTEntry;
typedef unsigned char IVTNo;
class KernelEv{
public:

	KernelEv(IVTNo ivtNo);
	~KernelEv();

	void wait();
	void signal();

	int binaryValue;
	PCB* ownerPCB;
	IVTNo ivtNo;
	IVTEntry* myIVTEntry;
	PCB* blockedPCB;

};


#endif /* KERNELEV_H_ */
