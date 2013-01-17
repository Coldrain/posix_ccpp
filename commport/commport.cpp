#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/time.h>
#include "Commport.h"

int speed_arr[] = { B115200, B57600, B38400, B19200, B9600, B4800, B2400,B1200, B300 };
unsigned int name_arr[] = { 115200, 57600, 38400, 19200, 9600, 4800, 2400,1200, 300 };

CCommport::CCommport() {
 hDev = INVALID_HANDLE_VALUE;
 mutex=new CMutex();
}

CCommport::~CCommport() {
 CloseSerial();
}

int CCommport::OpenSerial(const char *file) {
 hDev = open(file, O_RDWR | O_NOCTTY | O_NDELAY);
#ifdef DEBUG
 printf("port:%s id:%d\n", file, hDev);
#endif
 if (hDev >= 0)
 return 0;
 return INVALID_HANDLE_VALUE;
}

int CCommport::OpenSerial(const char *file, unsigned int BaudRate, char Parity,
 unsigned int DateBits, unsigned int StopBits) {
 int result = OpenSerial(file);
 if (result == 0) {
 if (SetBaudRate(BaudRate) != 0 || SetParity(Parity, DateBits, StopBits)!= 0) //´®¿Ú²ÎÊýÉèÖÃ
 {
 CloseSerial();
 return INVALID_HANDLE_VALUE;
 }
 }
 return result;

}

// È«¾Ö
// ¹Ø±Õ´®¿Ú
void CCommport::CloseSerial() {
 if (hDev > 0)
 close(hDev);
 hDev = INVALID_HANDLE_VALUE;
}

//ÉèÖÃ²¨ÌØÂÊ
int CCommport::SetBaudRate(unsigned int BaudRate) {
 int i;
 int result=-1;
 struct termios Opt;
 tcgetattr(hDev, &Opt);
 for (i = 0; i < 8; i++) {
 if (BaudRate == name_arr[i]) {
 tcflush(hDev, TCIOFLUSH); //Çå¿Õ´®¿ÚµÄ»º³åÇø
 cfsetispeed(&Opt, speed_arr[i]);
 cfsetospeed(&Opt, speed_arr[i]);
 result=tcsetattr(hDev, TCSANOW, &Opt);
 break;
 }
 }
 tcflush(hDev, TCIOFLUSH);//Çå¿Õ´®¿ÚµÄ»º³åÇø
 return result;
}

int CCommport::SetParity(char parity, unsigned int databits,
 unsigned int stopbits) {
 struct termios term;
 if (tcgetattr(hDev, &term) < 0)
 {
#ifdef DEBUG
 printf("Get Parity Failed\n");
#endif
 return -1;
 }
 term.c_cflag &= ~(CSIZE);
 switch (databits) {
 case 8:
 term.c_cflag |= CS8;
 break;
 default:
 term.c_cflag |= CS7;
 break;
 }

 switch (stopbits) {
 case 2:
 term.c_cflag |= CSTOPB;
 break;
 default:
 term.c_cflag &= ~CSTOPB;
 break;
 }
 switch (parity) {
 case 'o':
 case 'O':
 term.c_cflag |= (PARODD | PARENB);
 term.c_iflag |= INPCK;
 break;
 case 'e':
 case 'E':
 term.c_cflag |= PARENB;
 term.c_cflag &= ~PARODD;
 term.c_iflag |= INPCK;
 break;
 case 's':
 case 'S':
 term.c_cflag &= ~PARENB;
 term.c_cflag &= ~CSTOPB;
 term.c_iflag |= INPCK;
 break;
 case 'n':
 case 'N':
 term.c_cflag &= ~PARENB;
 term.c_iflag &= ~INPCK;
 break;
 default:
 term.c_cflag &= ~PARENB;
 term.c_iflag &= ~INPCK;
 break;

 }

 term.c_iflag &= ~(INLCR | ICRNL | BRKINT | IXON | IXOFF | IXANY);
 //term.c_lflag &= ~(ECHiONL|ECHO|IEXTEN|ISIG|ICANON);

 term.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//ECHiONL|ECHO|IEXTEN|ISIG|ICANON);

 term.c_oflag &= ~OPOST;
 term.c_cflag |= (CLOCAL | CREAD);
 // term.c_cflag |= CREAD;
 // term.c_iflag |=IGNPAR | IGNBRK;
 //
 tcflush(hDev, TCIFLUSH);
 // term.c_oflag=0;
 // term.c_lflag=0;
 term.c_cc[VMIN] = 0;
 term.c_cc[VTIME] = 30;//3Ãë
 if (tcsetattr(hDev, TCSANOW, &term) < 0)
 {
#ifdef DEBUG
 printf("Set Parity Failed\n");
#endif
 return -1;
 }
 return 0;
}

void CCommport::PrintDatetime(const char *header)
{
 char content[100];
 char datetime[50];
 struct timeval time;
 gettimeofday(&time,NULL);
 time_t t=time.tv_sec;
 struct tm *now=localtime(&t);
 memset(datetime,0,sizeof(datetime));
 strftime(datetime,20,"%Y-%m-%d %H:%M:%S",now);
 sprintf(content,"%s:%s.%03d\n",header,datetime,(int)time.tv_usec/1000);
 printf("%s\n",content);
}


int CCommport::ReadData(unsigned char* lpBuffer,
 unsigned int nNumberOfBytesToRead) {
 mutex->Lock();
 int BytesRead = read(hDev, lpBuffer, nNumberOfBytesToRead);
 mutex->UnLock();
#ifdef DEBUG
 if (BytesRead > 0) {
 printf("com recv len:%d data:",BytesRead);
 for (int i = 0; i < BytesRead; i++) {
 printf("%02X ", lpBuffer[i]);
 }
 printf("\n");
 }

#endif
 if (BytesRead < 0)
 BytesRead = 0;
 return BytesRead;
}

int CCommport::WriteData(unsigned char* lpBuffer,
 unsigned int nNumberOfBytesToWrite) {
#ifdef DEBUG
 printf("com %d write:",hDev);
 for (int i = 0; i < (int) nNumberOfBytesToWrite; i++) {
 printf("%02X ", lpBuffer[i]);
 }
 printf("\n");
#endif
 mutex->Lock();
 tcflush(hDev, TCOFLUSH);//Çå¿Õ´®¿ÚµÄ»º³åÇø
 int result=write(hDev, lpBuffer,nNumberOfBytesToWrite);
 mutex->UnLock();
 if(((unsigned int)result)==nNumberOfBytesToWrite)return 0;
 return -1;
}