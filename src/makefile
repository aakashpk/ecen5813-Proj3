#Makefile for ECEN 5813-002 Project 2
#Author Aakash Kumar

# Variables for compiler
CC=gcc
CCBBB=arm-linux-gnueabihf-gcc

# Compiler flags
CSTD=c99

#-Wall\

COMMONCFLAGS=-std=$(CSTD)\
	-O0
#	-Werror

HOSTCFLAGS=-g

CFLAGS=$(COMMONCFLAGS) $(HOSTCFLAGS)


include sources.mk

# Flag for cmocka unit test framework
TESTINCLUDE=-lcmocka


#preprocessor flags and
CPPFLAGS=-E
LDFLAGS=

#Set platform to build for as host machine by default
PLATFORM=HOST

#size tools for different platforms
SIZETOOL=size
SIZETOOLBBB=arm-linux-gnueabihf-size

.PHONY:build clean compile-all upload unittests flash

#compile time switches for verbose output
#and adding in
DS=VERBOSE
PS=

#List of files to be cleaned when running clean
TOREMOVE=$(OFILEPATH)/*.o\
	$(TESTTARGETS)\
	$(TARGET)\
	$(OFILEPATH)/*.map\
	*.asm\
	*.i\
	$(OFILEPATH)/*.d\
	$(OFILEPATH)/*.dep\

#target file names
CUR_TARGET=project3
TARGET=$(CUR_TARGET).elf
UPL_TARGET=project3_demo.elf
#TESTTARGET=../unit_tests/unittests.out
DISPOUT=./$(TARGET)

#folder paths to create .o files in seperate folder
#and not clutter the src folder
BINPATH=bin
OFILEPATH=obj
DEPFILES=dependencies
TESTSRCPATH=../unit_tests
TESTOBJPATH=../unit_tests/obj

#creating list of objects to be built based on source file
# these have been splitup to prevent errors from 2 main() s when
# test code and build code are built together

#common objects to be built for test and final build
COMMONOBJECTS:=$(addprefix $(OFILEPATH)/,$(COMMONSOURCES:%.c=%.o))

#objects for build
OBJECTS=$(addprefix $(OFILEPATH)/,$(MAINSOURCE:%.c=%.o)) $(COMMONOBJECTS)

#targets for test
TESTTARGETS:=$(addprefix $(TESTSRCPATH)/,$(TESTSOURCES:%.c=%.out))
#TESTTARGETS=$(TESTSOURCES:%.c=%.out)

#list of dependencies
DEPS:=$(addprefix $(OFILEPATH),$(OBJECTS:.o=.d))

#if platform is beaglebone black
#change compiler used
ifeq ($(PLATFORM),BBB)
CC = $(CCBBB)
SIZETOOL=$(SIZETOOLBBB)
DISPOUT=
else

#if platform is KL25Z, change compiler used and linker flags
#and add additional startup code/Include files for KL25Z
ifeq ($(PLATFORM),KL25Z)
CC = arm-none-eabi-gcc
SIZETOOL=arm-none-eabi-size
DS=KL25Z
INCLUDES+=-I ../include/CMSIS\
	-I ../include/kl25z
KL25ZCFLAG=-mthumb\
	-mcpu=cortex-m0plus\
	-fmessage-length=0\
	-g3\
	-fsigned-char\
	-ffunction-sections\
	-fdata-sections

CFLAGS=$(COMMONCFLAGS) $(KL25ZCFLAG)

LDFLAGS=-T ../platform/MKL25Z128xxx4_flash.ld\
	-specs=nosys.specs\
	-specs=nano.specs

OBJECTS+=$(addprefix $(OFILEPATH)/,$(KL25ZSOURCES:.c=.o))
OBJECTS+=$(addprefix $(OFILEPATH)/,$(ASSOURCES:.S=.o))
DISPOUT=
endif
endif

#Path where file is transferred to in the BBB when using the upload target
BBBPATH=/home/code/


-include $(DEPS)

#************* build rules ********************

#rule to run unit tests
unittests:$(TESTTARGETS)

# rule to build seperate out file for each unittest .c file and display
$(TESTSRCPATH)/%.out: $(TESTSRCPATH)/%.c $(COMMONOBJECTS)
	$(CC) $< -I$(INCLUDES) $(CFLAGS) -o $@ $(PS) $(TESTINCLUDE)	$(COMMONOBJECTS)
	./$(TESTSRCPATH)/$@


#rule to build the executable from all source files
build:$(OBJECTS)
	mkdir $(OFILEPATH) -p
	$(CC) $(OBJECTS) -I$(INCLUDES) $(CFLAGS) $(LDFLAGS) -o $(TARGET) -D$(DS) $(PS) -Xlinker -Map=$(OFILEPATH)/$(CUR_TARGET).map
#	@echo "\n******Built" $(TARGET)"******\n"
	$(SIZETOOL) $(OBJECTS) $(TARGET)
	$(DISPOUT)

flash:uart.elf
		gdb
		target remote localhost:7224
		load uart.elf

#building the executable for beaglebone black
#and transfer it directly to the board using scp
upload:$(OBJECTS)
	$(CCBBB) $(OBJECTS) -I$(INCLUDES) $(CFLAGS) $(LDFLAGS) -o $(TARGET) -D$(DS) $(PS) -Xlinker -Map=$(OFILEPATH)/$(CUR_TARGET).map
#	@echo "\n******Built" $(TARGET)"******\n"
	$(SIZETOOLBBB) $(OBJECTS) $(TARGET)
	scp $(TARGET) root@192.168.7.2:$(BBBPATH)$(TARGET)

#rule to just compile all	source files and not link
compile-all:$(OBJECTS)

$(OFILEPATH)/%.d : %.c
	mkdir $(OFILEPATH) -p
	$(CC) -MM $< -MF $@ -I$(INCLUDES) $(CFLAGS) $(CPPFLAGS) -D$(DS) $(LDFLAGS) $(PS)

%.i : %.c
	$(CC) $(CPPFLAGS) $< -o $@ -I$(INCLUDES) $(CFLAGS) $(LDFLAGS) -D$(DS) $(PS)

%.asm : %.c
	$(CC) -S $< -o $@ -I$(INCLUDES) $(CFLAGS) $(LDFLAGS) -D$(DS) $(PS)

%.o : %.S
#	mkdir $(OFILEPATH) -p
#	cp $< $@
	$(CC) -MMD -c $< -o $@ -I$(INCLUDES) $(CFLAGS) -D$(DS) $(PS)

#rule to compile build C files
$(OFILEPATH)/%.o : %.c
	mkdir $(OFILEPATH) -p
#	$(CC) -MM $< -MF $(OFILEPATH)/$*.dep -I $(INCLUDES) $(CFLAGS) $(PS)
	$(CC) -MMD -c $< -o $@ -I$(INCLUDES) $(CFLAGS) -D$(DS) $(PS)
#	@echo "\n******Built" $@"******"


#rule to delete objects created by build script
clean:
	rm -f $(TOREMOVE)
