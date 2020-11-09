/*
 * list.h
 *
 *  Created on: Sep 5, 2020
 *      Author: OS1
 */

#ifndef H_LIST_H_
#define H_LIST_H_

#include "Pcb.h"

class List {
	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB* p){
			pcb = p;
			next = 0;
		}
	};
public:
	Elem *first, *last;
	int sizeList; //duzina liste

	List();

	void addElem(PCB* p);
	PCB* searchInList(ID id);
	PCB* getFirstElem();
	void removeElem(PCB* p);
	void emptyList();
	virtual ~List();
};


#endif /* H_LIST_H_ */
