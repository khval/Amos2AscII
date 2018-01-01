
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>
#include <proto/exec.h>
#include "load_interpreter_config.h"

#define cmpID( a, b ) (*((int *) a) == *((int *) ((void *) b)))
#define Leek( adr )	*((int *) (adr))
#define Peek( adr ) *((char *) (adr))
#define Peek_str( adr, n ) strndup( adr , n )

const char *config_name = "AMOSPro_Interpreter_Config";

char *ST_str[STMX];

void process_load( char *mem )
{
	char *BNAME_str;
	char *F_str;
	char *ADAR;
	char *ADAT;
	char *STAD;
	char *A;
	int ST;
	int L;			// string length

	if (cmpID(mem,"PId1"))
	{
	         STAD=mem+Leek(mem+4)+8;
		if(cmpID(STAD,"PIt1"))
		{
			// Strings
			A=STAD+8;

			for (ST=1 ; ST<=STMX; ST++)
			{
				L=Peek(A+1) ;
				 if (L==0xFF) break;
				ST_str[ST-1]=Peek_str(A+2,L);
				A+=L+2;
			} 
		} 
	} 
}

BOOL load_config( const char *name )
{
	FILE *fd;
	size_t filesize;
	char *bank;
	BOOL ret = FALSE;

	fd = fopen(name,"r");
	if (fd)
	{	
		fseek(fd,0,SEEK_END);
		filesize = ftell(fd);
		fseek(fd,0,SEEK_SET);

		bank = (char *) malloc( filesize );

		if (bank)
		{
			if (fread( bank, filesize, 1, fd )==1)
			{
				process_load( bank );
			}

			ret = TRUE;
			free(bank);
		}

		fclose(fd);
	}
	return ret;
}

