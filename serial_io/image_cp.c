#include "mbed.h"
#include "USBSerial.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	int rows=512,cols=512;
    uint8_t image[rows*cols];
	uint8_t edge[rows*cols];
	char c;
	unsigned int i=0,j=0;
	float sigma=1.4;
	float tlow=0.4;
	float thigh=0.6;
	int 
    while(1)
    {	
	if(serial.readable())
	{
        serial.scanf("%c", &c);
		image[rows*i+j]=(uint8_t)c;
		j++;
		if(j>cols)
		{
			i++;
			j=0;
		}
		if(i>rows)
			break;
	}
    }
	i=0;
	j=0;
	while(1)
    {
	if(serial.writable())
	{
		c=(char)image[rows*i+j];
		serial.printf("%c",c);
		j++;
		if(j>cols)
		{
			i++;
			j=0;
		}
		if(i>rows)
			break;
	}
    }

}