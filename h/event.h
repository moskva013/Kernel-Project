/*
 * event.h
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_


#include "makro.h"

#define lock { asm pushf; asm cli; }
#define unlock asm popf

typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
	Event (IVTNo ivtNo);
	~Event ();
	void wait ();

protected:
	friend class IVTEntry;
	friend class KernelEv;


	void signal(); // can call KernelEv

private:
	KernelEv* myImpl;
};



#endif /* EVENT_H_ */
