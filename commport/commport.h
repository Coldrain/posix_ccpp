#ifndef __COMMPORT_H__
#define __COMMPORT_H__


#include "Mutex.h"

#define INVALID_HANDLE_VALUE -1

class CCommport {
public:
 CCommport();
 ~CCommport();
public:
 int ReadData(unsigned char* lpBuffer, unsigned int nNumberOfBytesToRead);
 int WriteData(unsigned char* lpBuffer, unsigned int nNumberOfBytesToWrite);

 int OpenSerial(int type, int port);
 int OpenSerial(int type, int port, unsigned int BaudRate, char Parity,
 unsigned int DateBits, unsigned int StopBits);
 int OpenSerial(const char *file);
 int OpenSerial(const char *file, unsigned int BaudRate, char Parity,
 unsigned int DateBits, unsigned int StopBits);

 void CloseSerial();
 int SetBaudRate(unsigned int BaudRate);
 int SetParity(char parity, unsigned int databits, unsigned int stopbits);

 void PrintDatetime(const char *header);
private:
 int hDev;
 CMutex *mutex;
};

#endif