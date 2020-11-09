/*
 * idle.cpp
 *
 *  Created on: Sep 6, 2020
 *      Author: OS1
 */
#include "idle.h"
#include "iostream.h"


extern int lockFlag;


Idle::Idle():Thread(defaultStackSize, 1){

}

void Idle::run(){

	while(1);





			//uki rekao da moze while(1)
				//ziza rekao da ne stavimo while(1) nego nesto pametnije jer ce mozda da odradi optimizaciju
				//ako nesto ne valja ovde probaj da popravis





}

void Idle::start(){

}


Idle::~Idle(){
	//lockFlag=0;
	//cout<<"Idle nit se unistila";
	//lockFlag=1;
	//PCB::idle->myPCB->finished = 1;
	this->setFinished();
}
