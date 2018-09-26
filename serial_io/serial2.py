import time
import serial
import re
import numpy
from PIL import Image
from matplotlib import pyplot

 #def read_pgm(filename, byteorder='>'):
#     """Return image data from a raw PGM file as numpy array.

#     Format specification: http://netpbm.sourceforge.net/doc/pgm.html

#     """
# filename='apple.PGM'
filename='32x32.PGM'
byteorder='<'
with open(filename, 'rb') as f:
    buffer = f.read()
try:
    header, width, height, maxval = re.search(
        b"(^P5\s(?:\s*#.*[\r\n])*"
        b"(\d+)\s(?:\s*#.*[\r\n])*"
        b"(\d+)\s(?:\s*#.*[\r\n])*"
        b"(\d+)\s(?:\s*#.*[\r\n]\s)*)", buffer).groups()
    print(len(header))
except AttributeError:
    raise ValueError("Not a raw PGM file: '%s'" % filename)

image=numpy.frombuffer(buffer,
                        dtype='u1' if int(maxval) < 256 else byteorder+'u2',
                        count=int(width)*int(height),
                        offset=len(header)
                        ).reshape((int(height), int(width)))

ser = serial.Serial('/dev/ttyACM0')

 #image=read_pgm(filename,byteorder='<')
print(image, image[31]) 
print('Enter your commands below.\r\nInsert "exit" to leave the application.')

print(image.shape)
ser.write(image[0:31,0:31])
time.sleep(5)
out = ''
size = 0
temp = ''
final2 = numpy.zeros([32*32])

while size < (32*32):
    temp = ord(ser.read())
    final2[size] = (temp)
    out += str(temp)
    size += 1

if out != '':
    print(">>" + out)  
print('size',size)  
final2 = numpy.reshape(final2, (32,32))
print('/n',final2)
ser.close()
pyplot.imshow(final2, pyplot.cm.gray)
pyplot.show()
# final=numpy.frombuffer(out,
#                             dtype='u1' if int(maxval) < 256 else byteorder+'u2',
#                             count=int(width)*int(height),
#                             offset=5
#                             ).reshape((int(height), int(width)))  
# print(final)

# input=1
# while 1 :
#     # get keyboard input
#     # input = raw_input(">> ")
#         # Python 3 users
#     #input = raw_input(">> ")
#     if input == 'exit':
#         ser.close()
#         exit()
#     else:
#         # send the character to the device
#         # (note that I happend a \r\n carriage return and line feed to the characters - this is requested by my device)

#         ser.write(input + '\r\n')
#         out = ''
#         # let's wait one second before reading output (let's give device time to answer)
#         time.sleep(1)
        # while ser.inWaiting() > 0:
        #     out += ser.read(1)

        # if out != '':
        #     print(">>" + out)

