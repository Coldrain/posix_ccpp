#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char input[128] = "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z";
	char *p = strtok(input, ",");
	while (p)
	{
		printf("%s\n", p);
		p = strtok(NULL, ",");
	}

	return 0;
}

