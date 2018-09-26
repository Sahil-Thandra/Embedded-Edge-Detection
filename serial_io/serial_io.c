#include "mbed.h"
#include "USBSerial.h"
 
//Virtual serial port over USB
USBSerial serial;
Serial pc(USBTX, USBRX);
 
int main(void) {
    uint8_t buf[128];
    while(1)
    {
        serial.scanf("%s", buf);
        serial.printf("recv: %s", buf);
        pc.printf("recv: %s\r\n", buf);
    }
}