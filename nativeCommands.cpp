
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <proto/exec.h>
#include "nativeCommands.h"
#include "amos2ascii.h"

struct nativeCommand Symbol[]=
{
	{0x005C,","},
	{0x0064,";"},
	{0x0074,"("},
	{0x007C,")"},
	{0x0084,"["},
	{0x008C,"]"},
	{0xFFC0,"+"},
	{0xFFCA,"-"},
	{0xFFA2,"="},
	{0xFFE2,"*"},
	{0xFFEC,"/"},
	{0xFFB6,">"},
	{0xFFAC,"<"},
	{0xFF8E,">="},	// numbers 
	{0xFF7A,"<="},	// numbers
	{0xFF98,">="},
	{0xFF84,"<="},
	{0xFF66,"<>"},
	{0xFFF6,"^"}
};


struct nativeCommand NativeCommand[]=
{
	{0x0054," :"},
	{0x0094," To"},
	{0x009C,"Not"},
	{0x00B0,"Def Fn"},
	{0x00BC," Fn"},
	{0x00F2,"Inkey$"},
	{0x012C,"Double Buffer"},
	{0x0140,"Start"},
	{0x014C,"Length"},
	{0x015A,"Doke"},
	{0x01DC,"Asc"},
	{0x01E6," As"},
	{0x0246,"Next"},
	{0x0286,"Loop "},
	{0x02A8,"Goto "},
	{0x02B2,"Gosub "},
	{0x02C6," then "},
	{0x02DA,"End if"},
	{0x02E6,"On Error"},
	{0x031E,"Resume Label"},
	{0x033C,"Pop Proc"},
	{0x0356," Step"},
	{0x0360,"Return" },
	{0x0386,"Proc"},
	{0x0390,"End Proc"},
	{0x039E,"Shared"},
	{0x03AA,"Global"},
	{0x03D6,"Param$"},
	{0x03E2,"Param"},
	{0x0426,"Break Off"},
	{0x0458,"Add"},
	{0x0462,"Add"},
	{0x0476,"Print "},
	{0x049C,"Input$"},
	{0x04B2,"Input"},
	{0x04BE,"Line Input"},
	{0x050E,"Mid$"},
	{0x0552,"Chr$"},
	{0x055E,"Space$"},
	{0x056C,"String$"},
	{0x057C,"Upper$"},
	{0x0598,"Str$"},
	{0x05A4,"Val"},
	{0x05DA,"Len"},
	{0x05E4,"Instr"},
	{0x060A,"Free"},
	{0x0640,"Dim"},
	{0x0670,"Edit"},
	{0x06AA,"Abs"},
	{0x06CA,"Degree"},
	{0x06EA,"Min"},
	{0x0702,"Sin"},	
	{0x070C,"Cos"},
	{0x072C,"Acos"},
	{0x0986,"Screen Copy"},
	{0x09A8,"Screen Copy"},
	{0x09EA,"Screen Open"},
	{0x0A04,"Screen Close "},
	{0x0A18,"Screen Display"},
	{0x0A36,"Screen Offset"},
	{0x0A5E,"Screen Color"},
	{0x0A88,"Screen To Front "},
	{0x0AA6,"Screen To Back "},
	{0x0AC0,"Screen Hide"},
	{0x0ADA,"Screen Show"},
	{0x0AE2,"Screen Swap"},
	{0x0AF4,"Screen Swap"},
	{0x0B58,"Screen Width"},
	{0x0B74,"Screen Height"},
	{0x0B90,"Get Palette"},
	{0x0BB8,"Cls"},
	{0x0C1E,"X Screen"},
	{0x0c38,"Y Screen"},
	{0x0C6E,"Screen"},		// setScreen
	{0x0C7C,"Screen"},	// getScreen
	{0x0C84,"Hires"},
	{0x2520,"Laced"},
	{0x0C90,"Lowres"},
	{0x0CCA,"Wait Vbl"},
	{0x0D1C,"Colour"},
	{0x0D34,"Flash Off"},
	{0x0DFE,"Fade"},
	{0x0E2C,"Autoback"},
	{0x0E3C,"Plot"},
	{0x0EC8,"Bar"},
	{0x0ED8,"Box"},
	{0x0F4A,"Text"},
	{0x1044,"Ink"},
	{0x1050,"Ink"},
	{0x11D8,"Key State"},
	{0x123E,"True"},
	{0x1248,"False"},
	{0x1262,"Scancode"},
	{0x129E,"Wait "},
	{0x1378,"Locate "},
	{0x1446,"Curs Off"},
	{0x15F2,"Y Curs"},
	{0x16B6,"Scin"},
	{0x16F2,"Set Input"},
	{0x1704,"Close Workbecnh"},
	{0x171A,"Close Editor"},
	{0x172C,"Dir First$"},
	{0x174E,"Exist"},
	{0x175A,"Dir$"},
	{0x17B6,"Set Dir"},
	{0x180C,"Bload"},
	{0x181A,"Bsave"},
	{0x187C,"Lof"},
	{0x18A8,"Open Random"},
	{0x18BC,"Open In"},
	{0x1900,"Close"},
	{0x190C,"Close"},
	{0x1930,"Kill"},
	{0x1948,"Field"},
	{0x1954,"Fsel$"},
	{0x1978,"Fsel$"},
	{0x1986,"Set Sprite Buffer"},
	{0x1A72,"Sprite Base"},
	{0x1B9E,"Bob"},
	{0x1DEA,"Show On"},
	{0x1E16,"X Mouse"},
	{0x1E24,"Y Mouse"},
	{0x1E32,"Mouse Key"},
	{0x1e6e,"Limit Mouse"},
	{0x1F94,"Channel"},
	{0x1FBC,"Amal on"},
	{0x1FCA,"Amal On"},
	{0x1FE2,"Amal off"},
	{0x2012,"Amal"},
	{0x20BA,"X Bob"},
	{0x20C6,"Y Bob"},
	{0x20F2,"Reserve As Work"},
	{0x210A,"Reserve As Chip Work"},
	{0x215E,"Erase"},
	{0x216A,"List Bank"},
	{0x217A,"Chip Free"},
	{0x218A,"Fast Free"},
	{0x21AA,"Copy"},
	{0x21CA,"Poke"},
	{0x21E6,"Peek"},
	{0x21F2,"Deek"},
	{0x23AC,"Put"},
	{0x23D0,"Multi Wait"},
	{0x23E0,"I Bob"},
	{0x2498,"Bank Swap"},
	{0x24AA,"Amos To Front"},
	{0x253C,"Command Line$"},
	{0x2578,"Set Accessory"},
	{0x259A,"Trap "},
	{0x2720,"Dialog Open"},
	{0x2764,"Dialog Close"},
	{0x277E,"Dialog Run"},
	{0x2796,"Dialog"},
	{0x27A4,"Vdialog"},
	{0x27B6,"Vdialog$"},
	{0x2824,"Dialog Update"},
	{0x287A,"Dialog Freeze"},
	{0x2898,"Dialog Unfreeze"},
	{0x28A0,"Poke$"},
	{0x28AE,"Peek$"},
	{0x28BE,"Peek$"},
	{0x28CA,"Resource Bank"},
	{0x28DE,"Resource$"},
	{0x2962,"Errtrap"},
	{0x2AB0,"Prg Under"},
	{0x2B58,"Screen Mode"},
	{0x2B72,"Kill Editor"},
	{0x4FE,"Set Buffers"},
	{0xFF4C,"or"},
	{0xFF58," and"},
	{0x1290,"Wait Key"},
	{0x0BD0,"Def Scroll"},
	{0x14E0,"Scroll"},
	{0x173E,"Dir Next$"},
	{0x06F6,"Max"},
	{0x17E4,"Load Iff"},
	{0x05AE,"Bin$"},
	{0x0536,"Right$"},
	{0x0E56,"Point"},
	{0x0D2C,"Colour"},
	{0x0EAC,"Polyline"},
	{0x0D44,"Flash"},
	{0x0F8A,"Get Disc Fonts"},
	{0x01BA,"Logbase"},
	{0x0FB2,"Set Font"},
	{0x184E,"Load"},
	{0x13DC,"Paper"},
	{0x13D2,"Pen"},
	{0x13E8,"Centre"},
	{0x10D6,"Zoom"},
	{0x0BAE,"Cls"},
	{0x1DD2,"Hide On"},
	{0x09D6,"Screen Clone"},
	{0x01F8,"Execall"},
	{0x0418,"Restore"},
	{0x040E,"Read"}
};

BOOL findSymbol(unsigned short token)
{
	struct nativeCommand *ptr;
	int size = sizeof(Symbol)/sizeof(struct nativeCommand);

	for (ptr =Symbol ; ptr < Symbol + size ; ptr++ )
	{
		if (token == ptr->id ) 
		{
			if ((token != 0x0074)&&(token != 0x005C))
			{
				if (last_token_is == is_command) printf(" ");
			}

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
