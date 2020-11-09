/*
 * event.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */


#include "event.h"
#include "KernelEv.h"


Event::Event(IVTNo ivtNo){
	lock;
	myImpl = new KernelEv(ivtNo);
	unlock;
}

Event::~Event(){
	lock;
	delete myImpl;
	unlock;

}

void Event::signal(){
	lock;
	myImpl->signal();
	unlock;

}

void Event::wait(){
	lock;
	myImpl->wait();
	unlock;

}
