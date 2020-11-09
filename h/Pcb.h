/*
 * Pcb.h
 *
 *  Created on: Sep 4, 2020
 *      Author: OS1
 */

#ifndef H_PCB_H_
#define H_PCB_H_

#include "thread.h"
#include "list.h"
#include "idle.h"


class List;

extern List *allThreads;

class PCB{
public:
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned finished;
	static PCB* running;
	static PCB* startingThread;
	static Idle* idle;
	Time myTSlice;
	ID myId;
	StackSize myStackSize;
	Thread* myThread;

	int endless; //ovo ti sluzi da regulises ako je timeSlice=0
	int created;
	int ready;
	int blocked;

	int leftTimeBlocked;	//koliko jos tikova pre nego sto se odblokira
	int flagReturnValueSemWait; //podrazumevano je 0
								//znaci stavicu ga na 1 kada se odblokira zbog isteka vremena


	List *blockedThreads;

	PCB(StackSize stackSize, Time timeSlice, Thread* thread);

	void static wrapper();

	~PCB();

protected:
	friend class Thread;

private:
	unsigned *stack;
};




#endif /* H_PCB_H_ */
