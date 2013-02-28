#include <stdio.h>
#include <string.h>

int main()
{
char SeatNo[5] = {0};
int i = 0;
strcpy(SeatNo, "0008");
while (SeatNo[i] == '0') i++;
printf("\n\n\n\n\n&SeatNo[i]: %s\n\n\n\n\n", &SeatNo[i]);
}
