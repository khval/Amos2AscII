
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <proto/exec.h>
#include "nativeCommands.h"

struct nativeCommand NativeCommand[]=
{
	{0xAC0,"Screen Hide"},
	{0x1e6e,"Limit Mouse"},
	{0x0094," To"},
	{0x03AA,"Global"},
	{0x0084,"["},
	{0x008C,"]"},
	{0x027E,"DO"}
};

BOOL findNativeCommand(unsigned short token)
{
	struct nativeCommand *ptr;
	int size = sizeof(NativeCommand)/sizeof(struct nativeCommand);

	for (ptr =NativeCommand ; ptr < NativeCommand + size ; ptr++ )
	{
		if (token == ptr->id ) 
		{
			printf("%s", ptr -> name);
			return TRUE;
		}
	}
	return FALSE;
}
