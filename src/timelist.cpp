/*
 * timelist.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#include "timelist.h"
#include "list.h"
#include "SCHEDULE.H"
#include "iostream.h"

extern int lockFlag;


TimeList::TimeList(){
	first = last = 0;
	sizeList = 0;
}

TimeList::~TimeList(){
	while(first) {
			Elem* old = first;
			first=first->next;
			delete old;
		}
}

void TimeList::addElem(PCB* p, KernelSem* s){
	Elem* newOne = new Elem(p,s);
		last = (!first ? first : last->next) = newOne;
		sizeList++;
}

void TimeList::removeElem(PCB* p){
		Elem* cur = first;
		Elem* prev = 0;
		while(cur){
			if(cur->pcb!=p){
				prev = cur;
				cur = cur->next;
			}else{
				Elem* old = cur;
				if(cur==last) last = prev;
				cur=cur->next;
				if(!prev) first = cur;
				else prev->next = cur;
				sizeList--;
				delete old;
				break; //mala optimizacija trebalo bi da ima smisla
			}
		}
}

//pazi ovde treba da postavis flagZaRetSem na 1
//i da vratis nit u skedzuler po potrebi
void TimeList::updateTimeList(){


	//lockFlag=0;


	Elem* cur = first;
	Elem* prev = 0;

/*
		lockFlag=0;
		cout<<"lista proba da se updejtuje broj elemenata u njoj je: "<<sizeList<<endl;
		lockFlag=1;

*/

	while(cur){

				/*lockFlag=0;
				cout<<"lista se updejtovala "<<cur->pcb->leftTimeBlocked<<endl;
				lockFlag=1;
				*/
		cur->pcb->leftTimeBlocked--;
		if(cur->pcb->leftTimeBlocked==0){

			cur->pcb->flagReturnValueSemWait=1;
			cur->sem->blockOnSem->removeElem(cur->pcb);
			cur->pcb->blocked=0;
			cur->pcb->ready=1;
			Scheduler::put(cur->pcb);

			Elem* old = cur;
			if(cur==last) last = prev;
			cur=cur->next;
			if(!prev) first = cur;
			else prev->next = cur;
			sizeList--;
			delete old;

		}else{
			prev = cur; //ovo sam dodaoooooo 15.09.3.57h
			cur=cur->next;
		}

	}
	//lockFlag=1;
}
