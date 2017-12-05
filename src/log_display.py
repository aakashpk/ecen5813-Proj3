import serial

ser = serial.Serial('COM3', 38400)

while(1):
    s = ser.read(10)
    print(s)