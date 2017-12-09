# ecen5813-Proj3
## Aakash Kumar / Arunsundar Kannan

The following table shows profiling values for the memory transfers. The values for the FRDM board are in clock cycles and the times for 
Beagle Bone Black is in microseconds.

|                          |          |           |            |            |  |                          |          |           |            |            | 
|--------------------------|----------|-----------|------------|------------|--|--------------------------|----------|-----------|------------|------------| 
| FRDM BOARD               |          |           |            |            |  | FRDM BOARD               |          |           |            |            | 
| (values in Clock Cycles) | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes |  | (values in Clock Cycles) | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes | 
| memmove                  | 142      | 952       | 9052       | 45052      |  | memset                   | 107      | 737       | 7037       | 35037      | 
| my_memmove               | 471      | 3801      | 37101      | 185101     |  | my_memset                | 397      | 3187      | 31087      | 155087     | 
| my_memmove (O3)          | 187      | 1267      | 12067      | 60067      |  | my_memset (O3)           | 152      | 1052      | 10052      | 50052      | 
| my_memmove_dma           | 667      | 775       | 4375       | 20379      |  | my_memset_dma            | 541      | 579       | 2379       | 10379      | 
|                          |          |           |            |            |  |                          |          |           |            |            | 
|                          |          |           |            |            |  |                          |          |           |            |            | 
| BEAGLE BONE BLACK        |          |           |            |            |  | BEAGLE BONE BLACK        |          |           |            |            | 
| (values in uS)           | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes |  | (values in uS)           | 10 bytes | 100 bytes | 1000 bytes | 5000 bytes | 
| memmove                  | 25       | 6         | 8          | 25         |  | memset                   | 18       | 5         | 5          | 13         | 
| my_memmove               | 7        | 17        | 128        | 623        |  | my_memset                | 6        | 13        | 94         | 454        | 
| my_memmove (O3)          | 5        | 7         | 28         | 122        |  | my_memset (O3)           | 4        | 6         | 20         | 88         | 


## Transfer Speed Observations
It can be observed that the on the KL25Z FRDM board the DMA transfers are the fastest, with 10byte transfer being the exception. 
This is probably because the overhead time to setup the DMA transfer is comparable to the transfer time for small transfers, but there is 
significant increase in efficiency for larger transfers. The standard library memmove and memset functions have fastest transfer speeds
after DMA. The O3 optimized my_memmove functions have significantly better transfer speeds than the my_memove function. The transfer
efficiency increases with size for all types of transfers. The same trends as memmove are observed for memset as well.

The transfer speeds on Beagele Bone Black are highest with the standard memove and memset functions. The O3 optimized my_memmove and my_memset 
have upto 4 times better speeds than the O0 compiled functions. The transfers get more efficient as the size of transfer increases.

## Logger Functionality
* The logger uses a circular buffer of structures of logdata type, this logs a logid enumeration, a timestamp in seconds since linux epoch 
 and a pointer to a payload and the length of the payload in logs that have a payload.
* The log log out to UART/standard out shows a comma seperated timestamp,enumvalue,payload,checksumerror value for each log.


## Extra credit
* log_display.py has a python script that can parse the raw logs from the logger and convert the seconds to meaningful date/time stamps. It converts
 all the enum numbers into the corresponding messages and displays the payloads if present. In case the logs have a checksum error, that is highlighted as well.
* Proper date/time is measured on the KL25Z by adding in a shell time at build time. The value obtained is passed to the RTC_TSR to act as the start time for the RTC 
 to have accurate timestamps
	
	makefile
	BT:=-Dbuildepochsec=$(shell date +"%s")
	
	rtc.c
	#ifdef buildepochsec
	RTC_TSR = buildepochsec; // passing the build time obtained from makefile
	#else
	RTC_TSR = 0;
	#endif
	
 

## Make file usage
* Using the "make PS=-DPROJECT3" command will enable the compile time switch for project3
* Using the "make PLATFORM=KL25Z"  will create the target executable to run on KL25Z
* Using the "make PLATFORM=BBB"  will create the target executable to run on Beagle Bone Black
* Using the "make build" command will create the target executable to run on HOSTMACHINE
* Running "make flash" can transfer the generated files from host machine to the freedom board