#ifndef PLATFORM_H
#define PLATFORM_H
/*
*@file platform.h
*@brief Wrapper around project1.h to prevent printfs in KL25Z
*@Author Aakash Kumar
*@date Oct 4 2017
*/

#ifdef KL25Z

/*void printdummy(char * dummy){
	
}*/	

#define printf //

#endif


#endif