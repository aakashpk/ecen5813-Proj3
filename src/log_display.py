#import serial

#ser = serial.Serial('COM3', 38400)

"""
while(1):
    s = ser.read(10)
    print(s)
    
"""
import time

log_enums=["LOGGER_INITIALZED",
	"GPIO_INITIALZED",
	"SYSTEM_INITIALIZED",
	"SYSTEM_HALTED",
	"INFO",
	"WARNING",
	"ERROR",
	"PROFILING_STARTED",
	"PROFILING_RESULT",
	"PROFILING_COMPLETED",
	"DATA_RECEIVED",
	"DATA_ANALYSIS_STARTED",
	"DATA_ALPHA_COUNT",
	"DATA_NUMERIC_COUNT",
	"DATA_PUNCTUATION_COUNT",
	"DATA_MISC_COUNT",
	"DATA_ANALYSIS_COMPLETED",
	"HEART_BEAT"]

f=open('logs.txt','r')

#buildepoch=1512780516
buildepoch=0

for line in f:
    temp_list=line.split(',')
    #print(line)
    if(temp_list[2]!=''):
        payload=temp_list[2]
    else:
        payload="No Payload"
        
    if(int(temp_list[3])==0):
        checksum_err="Checksum error"
    else:
        checksum_err="Checksum Ok"
        
    log_time=time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(int(temp_list[0])+buildepoch))
    log_val= log_enums[int(temp_list[1])]
        
    print("timestamp:",log_time, " logged:", log_val,"payload:", payload, " ",checksum_err)