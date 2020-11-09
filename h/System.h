/*
 * System.h
 *
 *  Created on: Sep 4, 2020
 *      Author: OS1
 */

#ifndef H_SYSTEM_H_
#define H_SYSTEM_H_

#include "Pcb.h"

extern void tick();

void interrupt timer();
void inic();
void restore();
void dispatch();



#endif /* H_SYSTEM_H_ */
