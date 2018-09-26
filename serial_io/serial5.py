import numpy as np
import cv2 
import serial

mo = cv2.imread('32x32.PGM',0)

h,w = mo.shape[:2]

mo = cv2.resize(mo,(64,64),interpolation = cv2.INTER_AREA)
new = np.zeros([60,60])

for i in range(64/32):
	for j in range(64/32):
		
		ser = serial.Serial('/dev/ttyACM0')
		mo_part = mo[i*32:i*32+32,j*32:j*32+32]
		cv2.imshow("image",mo_part)
		cv2.waitKey()
		cv2.destroyAllWindows()

		x = ser.read()
		print x
		for row in mo_part:
			for pix in row:
				pix = int(pix)
				ser.write(chr(pix))
		
		x = ser.read()
		print x		
		image = np.zeros([30,30])

		for k in range(900):
			x = ser.read()
			x = ord(x)
			print (x,k)
			image[(int)(k/30)][k%30] = x

		image = np.uint8(image)
		new[i*30:(i*30+30),j*30:(j*30+30)] = image
		ser.close()
		print(i,j)

print new[0:30,:]
print new[30:60,:]
cv2.imshow("image",new)
cv2.waitKey()
cv2.destroyAllWindows()