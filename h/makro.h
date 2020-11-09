/*
 * makro.h
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#ifndef MAKRO_H_
#define MAKRO_H_

#include "IVTEntry.h"
#include "KernelEv.h"
#include "thread.h"

#define PREPAREENTRY(numberEntry, callOld)\
void interrupt inter##numberEntry(...);\
IVTEntry entryNew##numberEntry(numberEntry, inter##numberEntry); \
void interrupt inter##numberEntry(...) {\
	entryNew##numberEntry.signal();\
	if (callOld == 1)\
	entryNew##numberEntry.callOldInt();\
}


#endif /* MAKRO_H_ */
