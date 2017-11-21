#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <proto/exec.h>
#include "nativeCommands.h"
#include "startup.h"
#include "amos2ascii.h"

struct Library 			 *AslBase = NULL;
struct AslIFace 		 *IAsl = NULL;

int token_is = is_newline;
int last_token_is = is_newline;

// structs are used read chunks of the AMOS file, so they need to be packed.

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

struct procedure
{
	unsigned int ProcLength;
	unsigned short seed;
	char flags;
	char seed2;
} __attribute__((packed)) ;

// etch special syntax and commands in AMOS need to be handled with care.

void cmdExtensionCommand(FILE *fd,char *ptr)
{
	struct extensionCommand *e = (struct extensionCommand *) ptr;
	printf("Command_%x_%x ", e->extention_number, e->ExtentionTokenTable);
}

void cmdCallProcedure(FILE *fd, char *ptr)
{
	char buffer[100];
	struct reference *ref = (struct reference *) ptr;
	int length2 = ref -> length + (ref -> length & 1);

	fread(buffer, length2, 1, fd);
	buffer[ ref -> length ] = 0;
	printf("%s",buffer);
}

void cmdLabelOnLine(FILE *fd, char *ptr)
{
	int what;
	char buffer[100];
	struct reference *ref = (struct reference *) ptr;
	int length2 = ref -> length + (ref -> length & 1);

	fread(buffer, length2, 1, fd);
	buffer[ ref -> length ] = 0;
	printf("%s:",buffer);
}


void cmdLabel(FILE *fd, char *ptr)
{
	int what;
	char buffer[100];
	struct reference *ref = (struct reference *) ptr;
	int length2 = ref -> length + (ref -> length & 1);

	fread(buffer, length2, 1, fd);
	buffer[ ref -> length ] = 0;
	printf("%s",buffer);
}

void cmdProcedure(FILE *fd, char *ptr)
{
	struct procedure *p = (struct procedure *) ptr;
	printf("Procedure ");
}

void cmdVar(FILE *fd, char *ptr)
{
	char buffer[100];
	struct reference *ref = (struct reference *) ptr;

	memset(buffer,'*', 50 );
	fread(buffer, ref -> length, 1, fd);

	buffer[ ref -> length ] = 0;
	printf("%s",buffer);
}

void cmdInt(FILE *fd,char *ptr)
{
	printf("%d", *((int *) ptr));
}

void cmdHex(FILE *fd,char *ptr)
{
	printf("$%08x", *((int *) ptr));
}

void cmdFor (FILE *fd,char *ptr)
{
	printf("For");
}

void cmdRepeat(FILE *fd,char *ptr)
{
	printf("Repeat");
}

void cmdWhile(FILE *fd,char *ptr)
{
	printf("While");
}

void cmdDo(FILE *fd,char *ptr)
{
	printf("Do");
}

void cmdIf(FILE *fd,char *ptr)
{
	printf("If");
}

void cmdExit(FILE *fd,char *ptr)
{
	printf("Exit");
}

void cmdElse(FILE *fd,char *ptr)
{
	printf("Else");
}

void cmdData(FILE *fd,char *ptr)
{
	printf("Data");
}

void cmdNewLine(FILE *fd,char *ptr)
{
	struct tokenStart *TokenStart = (struct tokenStart *) ptr;
	printf("\n");
}

void cmdDoubleQuotes(FILE *fd,char *ptr)
{
	unsigned short length = *((unsigned short *) ptr);
	unsigned short length2 = length;
	char *txt;

	length2 += (length & 1);		// align to 2 bytes
	txt = (char *) malloc(length2+1);

	if (txt)
	{
		txt[length] = 0;
		fread(txt,length2,1,fd);
		printf("%c%s%c",'"',txt,'"');
		free(txt);
	}
}

void cmdSingelQuotes(FILE *fd,char *ptr)
{
	unsigned short length = *((unsigned short *) ptr);
	unsigned short length2 = length;
	char *txt;

	length2 += (length & 1);		// align to 2 bytes
	txt = (char *) malloc(length2+1);

	if (txt)
	{
		txt[length] = 0;
		fread(txt,length2,1,fd);
		printf("%c%s%c",0x27,txt,0x27);
		free(txt);
	}
}

struct callTable{
	int id;
	int type;
	int size; 
	void (*fn) (FILE *fd,char *ptr);
};

struct callTable CallTable[] =
{
	{0x0000,	is_newline,	2,			cmdNewLine},
	{0x0026, is_string,		2,			cmdDoubleQuotes},
	{0x002E, is_string,		2,			cmdSingelQuotes},
	{0x0036, is_number,	sizeof(int),	cmdHex},
	{0x003E, is_number,	sizeof(int),	cmdInt},
	{0x004E, is_command,	sizeof(struct extensionCommand),cmdExtensionCommand},
	{0x0006, is_var,		sizeof(struct reference),cmdVar},
	{0x0012, is_procedure, 	sizeof(struct reference),cmdCallProcedure},
	{0x000C, is_newline,	sizeof(struct reference),cmdLabelOnLine},		// label on line
	{0x0018, is_var,		sizeof(struct reference),cmdLabel},		// ref
	{0x0376, is_newline,	sizeof(struct procedure),cmdProcedure},

	{0x029E, is_command, 4,cmdExit},
	{0x023C, is_command, 2,cmdFor},
	{0x0250, is_command, 2,cmdRepeat},
	{0x0268, is_command, 2,cmdWhile},
	{0x027E, is_command, 2,cmdDo},
	{0x02BE, is_command, 2,cmdIf},
	{0x02D0, is_command, 2,cmdElse},
	{0x0404, is_command, 2,cmdData},

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
			if (last_token_is == is_command) printf(" ");	// allways a space after commands?

			token_is = ptr -> type;
			fread(buffer, ptr->size, 1, fd);
			if (ptr->fn) ptr->fn( fd, buffer );
			return TRUE;
		} 
	}

	if (findSymbol(token))
	{
		token_is = is_symbol;
		return TRUE;
	}

	if (last_token_is == is_command) printf(" ");	// allways a space after commands?

	if (findNativeCommand(token))
	{
		token_is = is_command;
		return TRUE;
	}
	else
	{
		printf("\n\nERROR: File pos %08X -- Token %04X not found\n\n",  ftell(fd), token );
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
		last_token_is = token_is;
		fread( &TokenNumber, 2, 1, fd );	// next;
	}
}

bool init()
{
	if ( ! open_lib( "asl.library", 0L , "main", 1, &AslBase, (struct Interface **) &IAsl  ) ) return FALSE;
	return TRUE;
}

void closedown()
{
	if (IAsl) DropInterface((struct Interface*) IAsl); IAsl = 0;
	if (AslBase) CloseLibrary(AslBase); AslBase = 0;
}


int main( int args, char **arg )
{
	FILE *fd;
	char amosid[17];
	unsigned int tokenlength;
	char *filename = NULL;

	amosid[16] = 0;	// /0 string.

	if (init())
	{

		filename = get_filename(args,arg);

		if (!filename) filename = asl();

		if (filename)
		{
			fd = fopen(filename,"r");
			if (fd)
			{
				fread( amosid, 16, 1, fd );
				fread( &tokenlength, 4, 1, fd );

				printf( "%s, %d\n", amosid, tokenlength );

				code_reader( fd, tokenlength );

				fclose(fd);
			}
			free(filename);
		}
		closedown();
	}

	return 0;
}

