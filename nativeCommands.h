
struct nativeCommand
{
	int id;
	const char *name;
};

extern BOOL equal_symbol;
extern struct nativeCommand NativeCommand[];
extern BOOL findNativeCommand(unsigned short lastToken,unsigned short token);
extern BOOL findSymbol(unsigned short token);
extern int commandCnt;

