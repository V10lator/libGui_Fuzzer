#include <stdio.h>
#include <string.h>

#include "guiWrapper.h"

int main()
{	
	char text[7];
	strcpy(text, "Test ");
	char *nr = text + 5;
	
	initScreen();
	while(true)
	{
		for(int i = 0; i < 8; i++)
		{
			sprintf(nr, "%d", i);
			writeText(i, i, text);
		}
		drawScreen();
	}
	
	shutdownScreen();
	return 0;
}
