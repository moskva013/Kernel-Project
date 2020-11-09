/*
 * list.cpp
 *
 *  Created on: Sep 5, 2020
 *      Author: OS1
 */


#include "list.h"
#include "SCHEDULE.H"


List::List(){
	first = last = 0;
	sizeList = 0;
}

void List::addElem(PCB* p){
	Elem* newOne = new Elem(p);
	last = (!first ? first : last->next) = newOne;
	sizeList++;
}


List::~List(){
	while(first) {
		Elem* old = first;
		first=first->next;
		delete old;
	}
}

PCB* List::searchInList(ID id){
	Elem* cur = first;
	PCB* ret;
	while(cur){
		if(cur->pcb->myId==id){
			ret=cur->pcb;
			break;
		}
		cur=cur->next;
	}
	return ret;
}

PCB* List::getFirstElem(){
	if(first){
		Elem* cur = first;
		PCB* ret = cur->pcb;
		sizeList--;
		if(first->next){
			first = first->next;
		}
		else{
			first = last = 0;
		}
		delete cur; //ovde sam obrisao element iz liste
		return ret;
	}
	return 0;
}


void List::removeElem(PCB* p){
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

void List::emptyList(){
	while(first) {
			Elem* old = first;
			first->pcb->blocked=0;
			first->pcb->ready=1;
			Scheduler::put(first->pcb);
			first=first->next;
			sizeList--;
			delete old;
		}
	first = 0;
	last = 0;
}
