#ifndef KL25Z

#include "debug.h"
#include "memory.h"
#include "platform.h"



int main()
{

// Adds in project1 headers if project1 compile time switch given 
#ifdef PROJECT1
	#define NOPRINTDEFAULT
	#include "project1.h"	
	project1();
	
#endif	

// Adds in project2 headers if project2 compile time switch given 
#ifdef PROJECT2
	#define NOPRINTDEFAULT
	#include "project2.h"	
	project2();
	
#endif	

#ifdef PROJECT3
	#define NOPRINTDEFAULT
	#include "project3.h"
	PROJECT3_RUN();
#endif

// Default message when no project compile time switch given, help on how to add the project compile time switch
#ifndef NOPRINTDEFAULT
	
	printf("\nNo ProjectN Compile Time Switch, if you need it run \nmake clean \nand run ");
	printf("\nmake build PS=-DPROJECTn\nTo change platform\nadd PLATFORM= HOST/BBB/KL25Z\n\n");
	
#endif
return 0;

}


#else

#include "project3.h"


int main()
{

	project3_kl25z();
	

return 0;

}
	


#endif