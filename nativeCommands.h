
struct nativeCommand
{
	int id;
	const char *name;
};

extern struct nativeCommand NativeCommand[];
extern BOOL findNativeCommand(unsigned short token);
BOOL findSymbol(unsigned short token);

