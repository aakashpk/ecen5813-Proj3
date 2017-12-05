
MAINSOURCE= main.c

COMMONSOURCES= debug.c\
	memory.c\
	conversion.c\
	circularbuffer.c\
	project3.c\
	logger.c\
	logger_queue.c\
	profiler.c
	
KL25ZSOURCES=uart.c\
	project2.c\
	system_MKL25Z4.c\
	dma.c\
	led.c\
	profiler.c
	
ASSOURCES=startup_MKL25Z4.S
	
INCLUDES=../include/common

TESTSOURCES=test_circularbuffer.c\
	test_conversion.c\
	test_memory.c
