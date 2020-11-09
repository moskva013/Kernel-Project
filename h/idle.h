/*
 * idle.h
 *
 *  Created on: Sep 6, 2020
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_


#include "thread.h"


class Idle : public Thread{

public:
	Idle();
	~Idle();
	virtual void run();

	void start();

};


#endif /* IDLE_H_ */
