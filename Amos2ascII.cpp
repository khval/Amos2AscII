#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <proto/exec.h>
#include "nativeCommands.h"
#include "startup.h"
#include "amos2ascii.h"

struct Library 			 *AslBase = NULL;
struct AslIFace 		 *IAsl = NULL;

int token_is = is_newline;
int last_token_is = is_newline;

int commandCnt = 0;
int tokenCnt = 0;
int symbolCnt = 0;
int linenumber = 0;

char *filename = NULL;

BOOL equal_symbol = FALSE;

char space_after = 0;

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

struct rem
{
	unsigned short length;
};

BOOL token_reader( FILE *fd, unsigned short lastToken, unsigned short token, unsigned int tokenlength );

// etch special syntax and commands in AMOS need to be handled with care.

void cmdExtensionCommand(FILE *fd,char *ptr)
{
	struct extensionCommand *e = (struct extensionCommand *) ptr;
	printf("Command_%x_%x ", e->extention_number, e->ExtentionTokenTable);
}

void cmdRem(FILE *fd, char *ptr)
{
	char *buffer;
	struct rem *Rem = (struct rem *) ptr;
	int length2 = Rem -> length + (Rem -> length & 1);

	buffer = (char *) malloc(length2+1);
	if (buffer)
	{
		fread(buffer, length2, 1, fd);
		buffer[ Rem -> length ] = 0;
		printf("Rem %s",buffer);
		free(buffer);
	}
}

void cmdRem2(FILE *fd, char *ptr)
{
	char *buffer;
	struct rem *Rem = (struct rem *) ptr;
	int length2 = Rem -> length + (Rem -> length & 1);

	buffer = (char *) malloc(length2+1);
	if (buffer)
	{
		fread(buffer, length2, 1, fd);
		buffer[ Rem -> length ] = 0;
		printf("' %s",buffer);
		free(buffer);
	}
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
	const char *type[]={"","#","$","?"};
	struct reference *ref = (struct reference *) ptr;

	memset(buffer,'*', 50 );
	fread(buffer, ref -> length, 1, fd);

	buffer[ ref -> length ] = 0;

	if (space_after ==' ') printf(" ");
	space_after = 0;

	printf("%s",buffer);
	printf("%s",type[ref->flags&3] );

//	getchar();
}

void cmdInt(FILE *fd,char *ptr)
{
	if (space_after ==' ') printf(" ");
	space_after = 0;

	printf("%d", *((int *) ptr));
}

void cmdFloat(FILE *fd,char *ptr)
{
	unsigned int data = *((unsigned int *) ptr);
	unsigned int number1 = data >> 8;
	int e = (data & 31) ;
	if (data & 32) e |= 0xFFFFFFE0;
	int n;
	double f = 0.0f;

	if (space_after ==' ') printf(" ");
	space_after = 0;

	for (n=23;n>-1;n--)
	{
		if ((1<<n)&number1)
		{
			f += 1.0f / (double) (1<<(23-n));
		}
	}

	if (e>0)	f *= 1 <<e-1;
	if (e==0)	f /= 2;
	if (e<0)	f /= 1<<(-e+1);

	printf("%f", round( f *1000 ) / 1000.0f  );
}

void cmdHex(FILE *fd,char *ptr)
{
	if (space_after ==' ') printf(" ");
	space_after = 0;

	printf("$%08x", *((int *) ptr));
}


void cmdBin(FILE *fd,char *ptr)
{
	int num = *((int *) ptr);
	int n;
	int maxb;

	if (space_after ==' ') printf(" ");
	space_after = 0;

	printf("%%");

	maxb = 0;
	for (n=31;n>-1;n--)
	{
		if (num & (1<<n)) { maxb = n; break; }
	}

	for (n=maxb;n>-1;n--)
	{
		printf("%d",num & (1<<n) ? 1 : 0 );
	}
}


void cmdRepeat(FILE *fd,char *ptr)
{
	printf("Repeat");
}

void cmdDo(FILE *fd,char *ptr)
{
	printf("Do");
}

void cmdFor (FILE *fd,char *ptr)
{
	commandCnt = 0;
	space_after = 0;
	printf("For ");
}

void cmdWhile(FILE *fd,char *ptr)
{
	commandCnt = 0;
	space_after = 0;
	printf("While ");
}

void cmdUntil(FILE *fd,char *ptr)
{
	commandCnt = 0;
	space_after = 0;
	printf("Until ");
}

void cmdIf(FILE *fd,char *ptr)
{
	commandCnt = 0;
	space_after = 0;
	printf("If ");
}

void cmdOn(FILE *fd,char *ptr)
{
	commandCnt = 0;
	space_after = 0;
	printf("On ");
}

void cmdProc(FILE *fd,char *ptr)
{
	commandCnt = 0;
	space_after = 0;
	printf("Proc ");
}

void cmdExit(FILE *fd,char *ptr)
{
	printf("Exit");
}

void cmdElse(FILE *fd,char *ptr)
{
	printf("Else");
}

void cmdThen(FILE *fd,char *ptr)
{
	commandCnt = 0;
	space_after = 0;
	printf(" then ");
}

void cmdElseIf(FILE *fd,char *ptr)
{
	commandCnt = 0;
	space_after = 0;
	printf("Else If ");
}

void cmdExitIf(FILE *fd,char *ptr)
{
	printf("Exit If ");
}

void cmdData(FILE *fd,char *ptr)
{
	space_after = ' ';
	commandCnt = 0;
	printf("Data");
}

void cmdDivider(FILE *fd,char *ptr)
{
	space_after = 0;
	commandCnt = 0;
	equal_symbol = FALSE;
	printf(": ");
}

void cmdNewLine(FILE *fd,char *ptr)
{
	int n;
	struct tokenStart *TokenStart = (struct tokenStart *) ptr;
	linenumber++;
	printf("\n");
	for (n=1;n<TokenStart->level;n++) printf(" ");
	commandCnt = 0;
	space_after = 0;
}

void cmdDoubleQuotes(FILE *fd,char *ptr)
{
	unsigned short length = *((unsigned short *) ptr);
	unsigned short length2 = length;
	char *txt;

	if (space_after ==' ') printf(" ");
	space_after = 0;

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

	if (space_after ==' ') printf(" ");
	space_after = 0;

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
	{0x0006, is_var,		sizeof(struct reference),cmdVar},
	{0x000C, is_label,	sizeof(struct reference),cmdLabelOnLine},		// label on line
	{0x0012, is_procedure, 	sizeof(struct reference),cmdCallProcedure},
	{0x0018, is_var,		sizeof(struct reference),cmdLabel},		// ref
	{0x001E, is_number,	sizeof(int),	cmdBin},
	{0x0026, is_string,		2,			cmdDoubleQuotes},
	{0x002E, is_string,		2,			cmdSingelQuotes},
	{0x0036, is_number,	sizeof(int),	cmdHex},
	{0x003E, is_number,	sizeof(int),	cmdInt},
	{0x0046, is_number,	sizeof(int),	cmdFloat},
	{0x004E, is_command,	sizeof(struct extensionCommand),cmdExtensionCommand},
	{0x0054, is_commandDivider, 0, cmdDivider},
	{0x0376, is_newline,	sizeof(struct procedure),cmdProcedure},
	{0x0386, is_command, 0, cmdProc},
	{0x064A, is_newline,	sizeof(struct rem),cmdRem},
	{0x0652, is_newline,	sizeof(struct rem),cmdRem2},
	{0x3D45, is_newline,	sizeof(struct rem),cmdRem2},
	{0x029E, is_command, 4,cmdExit},
	{0x0034, is_command, 2,cmdExit},	// old exit command
	{0x023C, is_command, 2,cmdFor},
	{0x0250, is_command, 2,cmdRepeat},
	{0x0268, is_command, 2,cmdWhile},
	{0x025C, is_command, 0,cmdUntil},
	{0x027E, is_command, 2,cmdDo},
	{0x02BE, is_command, 2,cmdIf},
	{0x0316, is_command, 4,cmdOn},		// not unlike IF
	{0x02D0, is_command, 2,cmdElse},
	{0x0404, is_command, 2,cmdData},
	{0x25A4, is_command, 2,cmdElseIf},
	{0x0290, is_command, 4,cmdExitIf},
	{0x02C6, is_command, 0,cmdThen}
};

BOOL token_reader( FILE *fd, unsigned short lastToken, unsigned short token, unsigned int tokenlength )
{
	char buffer[1024];
	struct callTable *ptr;
	int size;

	if (token == 0)
	{
		if ( (ftell(fd)-20) == tokenlength ) 
		{
			printf("\n");
			return FALSE;
		}
	}

	size = sizeof(CallTable)/sizeof(struct callTable);
	for (ptr = CallTable; ptr < CallTable + size; ptr++ )
	{
		if (token == ptr->id ) 
		{
			if (ptr->type == is_command) commandCnt++;

			token_is = ptr -> type;
			fread(buffer, ptr->size, 1, fd);

			if (
				(last_token_is==is_var)||
				(last_token_is==is_label)||
				(last_token_is==is_string)||
				(last_token_is==is_number)||
				(lastToken == 0x007C)				// symbol ")"
			) printf(" ");

			if (ptr->fn) ptr->fn( fd, buffer );

			return TRUE;
		} 
	}

	if (findSymbol(token))
	{
		space_after = 0;
		tokenCnt++;
		token_is = is_symbol;
		return TRUE;
	}

	if (findNativeCommand(lastToken, token))
	{
		commandCnt++;
		token_is = is_command;
		return TRUE;
	}
	else
	{
		printf("\n\nERROR: Line %d, File pos %08X -- Token %04X not found\n",linenumber, ftell(fd), token );
		printf("FILE: %s\n\n", filename);
	}

	return FALSE;
}

void code_reader( FILE *fd, unsigned int  tokenlength)
{
	struct tokenStart TokenStart;
	unsigned short LastTokenNumber=0;
	unsigned short TokenNumber;

	token_reader(fd, 0, 0 , tokenlength);	// new line

	fread( &TokenNumber, 2, 1, fd );
	while (token_reader( fd, LastTokenNumber, TokenNumber, tokenlength ))
	{
		LastTokenNumber = TokenNumber;
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
				code_reader( fd, tokenlength );
				fclose(fd);
			}
			free(filename);
		}
		closedown();
	}

	return 0;
}

