/*

 * System.cpp
 *
 *  Created on: Sep 4, 2020
 *      Author: OS1
 */



#include <dos.h>
#include <iostream.h>
#include <System.h>
#include <Pcb.h>
#include <SCHEDULE.H>
#include "idle.h"
#include "KernSem.h"
#include "timelist.h"



#define lock asm cli


#define unlock asm sti



volatile int cntr;
volatile unsigned tsp;
volatile unsigned tss;
volatile unsigned tbp;
volatile int context_switch_on_demand = 0;
volatile unsigned int lockFlag = 1;

extern PCB* startingThread;
extern PCB* running;

// stara prekidna rutina
unsigned oldTimerOFF, oldTimerSEG;

int flagIdle = 0;//dodao 16.9 ovo koristis u destruktoru idle niti

void inic(){
	asm{
			cli
			push es
			push ax

			mov ax,0
			mov es,ax // es = 0

			// pamti staru rutinu
			mov ax, word ptr es:0022h
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax

			// postavlja novu rutinu

			mov word ptr es:0022h, seg timer
			mov word ptr es:0020h, offset timer

			// postavlja staru rutinu na int 60h
			mov ax, oldTimerSEG
			mov word ptr es:0182h, ax
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax

			pop ax
			pop es
			sti
		}

	PCB::startingThread = new PCB(defaultStackSize, defaultTimeSlice, 0);
	PCB::running = PCB::startingThread;
	PCB::running->ready = 1;

	PCB::idle = new Idle();

}

void restore(){

	asm {
			cli
			push es
			push ax

			mov ax,0
			mov es,ax

			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
			sti
		}

	delete PCB::idle;
	delete PCB::startingThread;
	flagIdle = 1;
	delete allThreads;

	//cout<<"RESTORE";

}



void interrupt timer(){

	if(!context_switch_on_demand) {
		cntr--;

		tick();
		KernelSem::timelist->updateTimeList();
		asm int 60h;
	}

	if(PCB::running->endless){

		if (context_switch_on_demand) {
				if(lockFlag){
					context_switch_on_demand = 0;
				asm {
					// cuva sp
					mov tsp, sp
					mov tss, ss
					mov tbp, bp
				}

				lockFlag=0;

				PCB::running->sp = tsp;
				PCB::running->ss = tss;
				PCB::running->bp = tbp;


				asm cli; // u nekim slucajevima se desi da se prekidi omoguce kaze Milana i zato ovo ostavljam ipak

				lockFlag=1;
				// scheduler
				if(!PCB::running->finished && !PCB::running->blocked && PCB::running != PCB::idle->getPCB()) Scheduler::put((PCB*)PCB::running);
																										//znaci ukoliko nije blokirana ili zavrsena
				PCB::running = Scheduler::get();														//stavljam je u scheduler + idle se ne stavlja u skedzuler


				if(PCB::running == 0) PCB::running = PCB::idle->getPCB();

				tsp = PCB::running->sp;
				tss = PCB::running->ss;
				tbp = PCB::running->bp;

				cntr = PCB::running->myTSlice;  //ovde svakako sad uzimas novi PCB tako da nema gimnastike

				asm {
					// restaurira sp
					mov sp, tsp
					mov ss, tss
					mov bp, tbp
				}
			}
			else context_switch_on_demand = 1;
		}
	} // ovo je zagrada pomocu koje si regulisao ono za time slice
	else{
		if (cntr==0 || context_switch_on_demand) {
					if(lockFlag){
						context_switch_on_demand = 0;
					asm {
						// cuva sp
						mov tsp, sp
						mov tss, ss
						mov tbp, bp
					}

					lockFlag=0;

					PCB::running->sp = tsp;
					PCB::running->ss = tss;
					PCB::running->bp = tbp;

					asm cli; // u nekim slucajevima se desi da se prekidi omoguce
					// unutar cout<<...
					lockFlag=1;
					// scheduler

					if(!PCB::running->finished && !PCB::running->blocked && PCB::running != PCB::idle->getPCB()) Scheduler::put((PCB*)PCB::running);
					PCB::running = Scheduler::get();

					//ovde treba uslov ako su sve niti blokirane da running stavimo na idle nit
					if(PCB::running == 0) PCB::running = PCB::idle->getPCB();

					tsp = PCB::running->sp;
					tss = PCB::running->ss;
					tbp = PCB::running->bp;

					cntr = PCB::running->myTSlice;  //ovde svakako sad uzimas novi PCB tako da nema gimnastike

					asm {
						// restaurira sp
						mov sp, tsp
						mov ss, tss
						mov bp, tbp
					}
				}
				else context_switch_on_demand = 1;
			}
	}



}


// sinhrona promena konteksta
void dispatch(){
	lock
	context_switch_on_demand = 1;
	timer();
	unlock
}

