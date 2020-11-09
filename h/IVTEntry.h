/*
 * IVTEntry.h
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "KernelEv.h"
//#include "makro.h"

typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;
class KernelEv;
class IVTEntry{
public:

	IVTEntry(IVTNo ivtNo, pInterrupt newRoutine);
	~IVTEntry();

	void signal();
	void callOldInt();

	static IVTEntry* IVT[256];

	pInterrupt oldRoutine;
	IVTNo ivtNo;
	KernelEv* myKernelEv;


};



#endif /* IVTENTRY_H_ */
