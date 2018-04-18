
struct nativeCommand
{
	int id;
	const char *name;
};

extern BOOL equal_symbol;
extern struct nativeCommand NativeCommand[];
extern int findNativeCommand(unsigned short lastToken,unsigned short token);
extern BOOL findSymbol(unsigned short token);
extern int commandCnt;

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


