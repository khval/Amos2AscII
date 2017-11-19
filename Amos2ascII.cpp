#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <proto/exec.h>
#include "nativeCommands.h"


BOOL last_command = FALSE;

struct tokenStart {
	char length;
	char level;
} __attribute__((packed)) ;

struct extensionCommand
{
	unsigned char extention_number;
	unsigned char alignment16bit;			// maybe length
	unsigned short ExtentionTokenTable;
} __attribute__((packed)) ;

struct reference
{
	short unknown;
	char	length;
	char flags;
} __attribute__((packed)) ;

void cmdExtensionCommand(FILE *fd,char *ptr)
{
	struct extensionCommand *e = (struct extensionCommand *) ptr;
	printf("Command_%x_%x ", e->extention_number, e->ExtentionTokenTable);
}

void cmdCallProcedure(FILE *fd, char *ptr)
{
	char buffer[100];

	struct reference *ref = (struct reference *) ptr;
	fread(buffer, ref -> length, 1, fd);
	buffer[ ref -> length ] = 0;
	printf("%s",buffer);
}

void cmdVar(FILE *fd, char *ptr)
{
	char buffer[100];
	struct reference *ref = (struct reference *) ptr;

	memset(buffer,'*', 50 );
	fread(buffer, ref -> length, 1, fd);

	buffer[ ref -> length ] = 0;

	if (last_command) printf(" ");
	printf("%s",buffer);
}

void cmdInt(FILE *fd,char *ptr)
{
	if (last_command) printf(" ");
	printf("%d", *((int *) ptr));
}

void cmdComma(FILE *fd,char *ptr)
{
	printf(",");
}

void cmdPlus(FILE *fd,char *ptr)
{
	printf("+");
}

void cmdMinus(FILE *fd,char *ptr)
{
	printf("-");
}

void cmdNewLine(FILE *fd,char *ptr)
{
	struct tokenStart *TokenStart = (struct tokenStart *) ptr;
//	printf("\nlength %d level %d\n", TokenStart->length * 2, TokenStart->level );
	printf("\n");
}

struct callTable{
	int id;
	int size; 
	void (*fn) (FILE *fd,char *ptr);
};

struct callTable CallTable[] =
{
	{0x0000,2,cmdNewLine},
	{0x003E,sizeof(int),cmdInt},
	{0x004E,sizeof(struct extensionCommand),cmdExtensionCommand},
	{0x005C,0,cmdComma},
//	{0x0094,0,cmdMinus},
	{0xFFC0,0,cmdPlus},
	{0x0006,sizeof(struct reference),cmdVar},
	{0x0012,sizeof(struct reference),cmdCallProcedure}
};


BOOL token_reader( FILE *fd, unsigned token )
{
	char buffer[1024];
	struct callTable *ptr;
	int size;

	size = sizeof(CallTable)/sizeof(struct callTable);
	
	for (ptr = CallTable; ptr < CallTable + size; ptr++ )
	{
		if (token == ptr->id ) 
		{
			fread(buffer, ptr->size, 1, fd);
			if (ptr->fn) ptr->fn( fd, buffer );
			last_command = FALSE;
			return TRUE;
		} 
	}

	if (findNativeCommand(token))
	{
		last_command = TRUE;
		return TRUE;
	}
	else
	{
		printf("Token %04x not found\n", token );
	}

	return FALSE;
}

void code_reader( FILE *fd, unsigned int  tokenlength)
{
	struct tokenStart TokenStart;
	unsigned short TokenNumber;

	token_reader(fd, 0 );	// new line

	fread( &TokenNumber, 2, 1, fd );
	while (token_reader( fd, TokenNumber ))
	{
		fread( &TokenNumber, 2, 1, fd );	// next;
	}
}

int main( int args, char **arg )
{
	FILE *fd;
	char amosid[17];
	unsigned int tokenlength;

	amosid[16] = 0;	// /0 string.

	if (args!=2) return 0;

	fd = fopen(arg[1],"r");
	if (fd)
	{
		fread( amosid, 16, 1, fd );
		fread( &tokenlength, 4, 1, fd );

		printf( "%s, %d\n", amosid, tokenlength );

		code_reader( fd, tokenlength );

		fclose(fd);
	}

	return 0;
}

