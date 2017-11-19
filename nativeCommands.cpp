
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <proto/exec.h>
#include "nativeCommands.h"

struct nativeCommand Symbol[]=
{
	{0x005C,","},
	{0xFFC0,"+"},
	{0xFFA2,"="},
	{0xFFEC,"/"},
	{0xFFB6,">"},
	{0xFFAC,"<"}
};


struct nativeCommand NativeCommand[]=
{
	{0xAC0,"Screen Hide"},
	{0x1e6e,"Limit Mouse"},
	{0x0094," To"},
	{0x03AA,"Global"},
	{0x0084,"["},
	{0x008C,"]"},
	{0x0C1E,"X Screen"},
	{0x0c38,"Y Screen"},
	{0x0074,"("},
	{0x007C,")"},
	{0x1E16,"X Mouse"},
	{0x1E24,"Y Mouse"},
	{0x1E32,"Mouse Key"},
	{0x16B6,"Scin"},
	{0xFF58," and"},
	{0x02C6," then "},
	{0x0C6E,"Screen"},		// setScreen
	{0x0C7C,"Screen"},	// getScreen
	{0x0A04,"Screen Close "},
	{0x0AA6,"Screen To Back "},
	{0x0A88,"Screen To Front "},
	{0x0054," : "},
	{0x259A,"Trap "},
	{0x129E,"Wait "},
	{0x1378,"Locate "},
	{0x0476,"Print "},
	{0x0286,"Loop "},
//	{0x2962,"Unkown "},
};

BOOL findSymbol(unsigned short token)
{
	struct nativeCommand *ptr;
	int size = sizeof(Symbol)/sizeof(struct nativeCommand);

	for (ptr =Symbol ; ptr < Symbol + size ; ptr++ )
	{
//		printf("token %04x, Symbol: %04x, %s\n", token, ptr->id, ptr-> name);

		if (token == ptr->id ) 
		{
			printf("%s", ptr -> name);
			return TRUE;
		}
	}
	return FALSE;
}

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
