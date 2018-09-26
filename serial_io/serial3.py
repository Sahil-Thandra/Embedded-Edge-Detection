import serial
ser = serial.Serial(port='/dev/ttyACM0', baudrate=9600)  # open first serial port
print(ser)   # check which port was really used
print(("hello").encode())
ser.write(("hello").encode())      # write a string
ser.close()             # close port
