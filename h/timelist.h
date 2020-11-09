/*
 * timelist.h
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#ifndef TIMELIST_H_
#define TIMELIST_H_

//#include "semaphor.h"
#include "KernSem.h"

class PCB;

class TimeList {
	struct Elem{
		PCB* pcb;
		KernelSem* sem;
		Elem* next;
		Elem(PCB* p, KernelSem* s){
			sem = s;
			pcb = p;
			next = 0;
		}
	};
public:
	Elem *first, *last;
	int sizeList; //duzina liste

	TimeList();

	void addElem(PCB* p, KernelSem* s);
	void removeElem(PCB* p);
	void updateTimeList();

	~TimeList();
};




#endif /* TIMELIST_H_ */
