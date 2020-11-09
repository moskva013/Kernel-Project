/*
 * main.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: OS1
 */

#include <iostream.h>
#include "System.h"


int userMain(int argc, char** argv);

int main(int argc, char* argv[]){

	inic();

	int ret = userMain(argc,argv);

	restore();

	return ret;
}

