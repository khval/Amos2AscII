
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
	{0x0094,"To"},
	{0x009C,"Not"},
	{0x00A6,"Swap"},
	{0x00B0,"Def Fn"},
	{0x00BC," Fn"},
	{0x00C4,"Follow Off" },
	{0x00D4,"Follow" },
	{0x00E0,"Resume Next"},
	{0x00F2,"Inkey$"},
	{0x00FE,"Repeat$"},
	{0x010E,"Zone$"},
	{0x011C,"Border$"},
	{0x012C,"Double Buffer" },
	{0x0140,"Start" },
	{0x014C,"Length" },
	{0x015A,"Doke" },
	{0x0168,"On Menu Del" },
	{0x017A,"On Menu On" },
	{0x018A,"On Menu Off" },
	{0x019C,"Every On" },
	{0x01AA,"Every Off" },
	{0x01BA,"Logbase" },
	{0x01C8,"Logic" },
	{0x01D4,"Logic" },
	{0x01DC,"Asc" },
	{0x01E6,"As" },
	{0x01EE,"Call" },
	{0x01F8,"Execall" },
	{0x0206,"Gfxcall" },
	{0x0214,"Doscall" },
	{0x0222,"Intcall" },
	{0x0246,"Next"},
	{0x0274,"Wend"},
	{0x0286,"Loop"},
	{0x02A8,"Goto "},
	{0x02B2,"Gosub"},
	{0x02DA,"End if"},
	{0x02E6,"On Error"},
	{0x02F4,"On Break Proc"},
	{0x0308,"On Menu"},
	{0x0316,"On"},
	{0x031E,"Resume Label"},
	{0x0330,"Resume"},
	{0x033C,"Pop Proc"},
	{0x034A,"Every"},
	{0x0356,"Step"},
	{0x0360,"Return"},
	{0x036C,"Pop"},
	{0x0386,"Proc"},
	{0x0390,"End Proc"},
	{0x039E,"Shared"},
	{0x03AA,"Global"},
	{0x03B6,"End"},
	{0x03C0,"Stop"},
	{0x03CA,"Param#"},
	{0x03D6,"Param$"},
	{0x03E2,"Param"},
	{0x03EE,"Error"},
	{0x03FA,"Errn"},
	{0x040E,"Read"},
	{0x0418,"Restore"},
	{0x0426,"Break Off"},
	{0x0436,"Break On"},
	{0x0444,"Inc"},
	{0X044E,"Dec"},
	{0x0458,"Add"},
	{0x0462,"Add"},
	{0x046A,"Print #"},		// Print to file
	{0x0476,"Print"},
	{0x0482,"Lprint"},
	{0x048E,"Input$"},		//	=Input$(max)
	{0x049C,"Input$"},
	{0x04A6,"Using"},
	{0x04B2,"Input"},
	{0x04BE,"Line Input #" },
	{0x04D0,"Input" },
	{0x04DC,"Line Input" },
	{0x04EC,"Run" },
	{0x04F6,"Run" },
	{0x04FE,"Set Buffers"},
	{0x050E,"Mid$"},	// Mid$(txt,start,len)
	{0x051E,"Mid$"},	// Mid$(txt,start)
	{0x0528,"Left$"},
	{0x0536,"Right$"},
	{0x0546,"Flip$"},
	{0x0552,"Chr$"},
	{0x055E,"Space$"},
	{0x056C,"String$"},
	{0x057C,"Upper$"},
	{0x058A,"Lower$"},
	{0x0598,"Str$"},
	{0x05A4,"Val"},
	{0x05AE,"Bin$"},
	{0x05BA,"Bin$"},	// = Bin$(num,max)
	{0x05C4,"Hex$"},
	{0x05D0,"Hex$"},
	{0x05DA,"Len"},
	{0x05E4,"Instr"},	// Instr(str,str)
	{0x05F4,"Instr"},	// Instr(str,str,n)
	{0x0600,"Tab$"},
	{0x060A,"Free"},
	{0x0614,"Varptr"},
	{0x0620,"Remember X"},
	{0x0630,"Remember Y" },
	{0x0640,"Dim"},
	{0x0658,"Sort"},	// Sort( array )
	{0x0662,"Match"},	// =Match( array, str )
	{0x0670,"Edit"},
	{0x067A,"Direct"},
	{0x0686,"Rnd"},
	{0x0690,"Randomize" },
	{0x06A0,"Sgn"},
	{0x06AA,"Abs"},
	{0x06B4,"Int"},		// =Int( v# )
	{0x06BE,"Radian" },
	{0x06CA,"Degree" },
	{0x06D6,"Pi#" },
	{0x06E0,"Fix" },
	{0x06EA,"Min" },
	{0x06F6,"Max" },
	{0x0702,"Sin" },
	{0x070C,"Cos" },
	{0x0716,"Tan" },
	{0x0720,"Asin" },
	{0x072C,"Acos" },
	{0x0738,"Atan" },
	{0x0744,"Hsin" },
	{0x0750,"Hcos" },
	{0x075C,"Htan" },
	{0x0768,"Sqr" },
	{0x0772,"Log" },
	{0x077C,"Ln" },
	{0x0786,"Exp" },
	{0x0790,"Menu To Bank" },
	{0x07A4,"Bank To Menu" },
	{0x07B8,"Menu On"},
	{0x07C6,"Menu Off"},
	{0x084E,"Menu Key"},
	{0x08FC,"Menu Inactive"},
	{0x0956,"Menu Del"},
	{0x0964,"Menu$"},
	{0x0970,"Choice"},
	{0x097E,"Choice"},		// Choice(1)
	{0x0986,"Screen Copy"},
	{0x09A8,"Screen Copy"},
	{0x09D6,"Screen Clone"},
	{0x09EA,"Screen Open"},
	{0x0A04,"Screen Close "},
	{0x0A18,"Screen Display"},
	{0x0A36,"Screen Offset"},
	{0x0A4E,"Screen Size"},
	{0x0A5E,"Screen Color"},
	{0x0A72,"Screen To Front"},		// Screen To Front n
	{0x0A88,"Screen To Front"},
	{0x0A90,"Screen To Back"},		// No args
	{0x0AA6,"Screen To Back"},
	{0x0AAE,"Screen Hide"},		// Screen Hide n
	{0x0AC0,"Screen Hide"},
	{0x0AC8,"Screen Show"},		// Screen Show with out args
	{0x0ADA,"Screen Show"},
	{0x0AE2,"Screen Swap"},
	{0x0AF4,"Screen Swap"},
	{0x0B16,"View"},				// View
	{0x0B20,"Auto View Off"},
	{0x0B34,"Auto View On"},
	{0x0B46,"Screen Base"},
	{0x0B58,"Screen Width"},
	{0x0B74,"Screen Height"},
	{0x0B90,"Get Palette"},
	{0x0BAE,"Cls"},
	{0x0BB8,"Cls"},
	{0x0BC0,"Cls"},	// CLS color,x,y to x,y
	{0x0BD0,"Def Scroll"},
	{0x0BEE,"X Hard"},
	{0x0C06,"Y Hard"},
	{0x0C1E,"X Screen"},
	{0x0C2E,"X Screen"}, 	// X Screen( screen, x )
	{0x0C38,"Y Screen"},
	{0x0C48,"Y Screen"},	// Y Screen( screen, y )
	{0x0C52,"X Text"},
	{0x0C60,"Y Text"},
	{0x0C6E,"Screen"},		// setScreen
	{0x0C7C,"Screen"},	// getScreen
	{0x0C84,"Hires"},
	{0x0C90,"Lowres"},
	{0x0C9C,"Dual Playfield"},
	{0x0CB4,"Dual Priority"},
	{0x0CCA,"Wait Vbl"},
	{0x0CD8,"Default Palette"},
	{0x0CEE,"Default"},
	{0x0CFC,"Palette"},
	{0x0D0A,"Colour Back"},
	{0x0D1C,"Colour"},
	{0x0D2C,"Colour"},
	{0x0D34,"Flash Off"},
	{0x0D44,"Flash"},
	{0x0D52,"Shift Off"},
	{0x0D62,"Shift Up"},
	{0x0D78,"Shift Down"},
	{0x0D90,"Set Rainbow"},		// Set Rainbow V(1),V(2),V(3),V$(4),V$(5),V$(6)
	{0x0DC2,"Rainbow Del"},
	{0x0DD4,"Rainbow Del"},		// Rainbow Del n
	{0x0DDC,"Rainbow"},			// Rainbow V(1),V(2),V(3),V(4)
	{0x0DF0,"Rain"},
	{0x0DFE,"Fade"},
	{0x0E08,"Phybase"},		// =Phybase(n)
	{0x0E24,"Physic"},
	{0x0E2C,"Autoback"},
	{0x0E3C,"Plot"},
	{0x0E4A,"Plot"},
	{0x0E56,"Point"},
	{0x0E64,"Draw"},			// Draw To x,y
	{0x0E74,"Draw"},			// Draw x,y To X,y
	{0x0E86,"Ellipse"},			// Ellipse x,y,rx,ry
	{0x0E9A,"Circle"},			// Circle x,y,r
	{0x0EAC,"Polyline"},
	{0x0EBA,"Polygon"},
	{0x0EC8,"Bar"},
	{0x0ED8,"Box"},
	{0x0EE8,"Paint"},
	{0x0F04,"Gr Locate"},
	{0x0F16,"Text Length"},
	{0x0F3A,"Text Base"},
	{0x0F4A,"Text"},
	{0x0F5A,"Set Text"},
	{0x0F6A,"Set Paint"},
	{0x0F7A,"Get Fonts"},
	{0x0F8A,"Get Disc Fonts"},
	{0x0FB2,"Set Font"},
	{0x0FC2,"Font$"},
	{0x0FCE,"Hslider"},		// Hslider n,n To n,n,n,n,n
	{0x0FE8,"Vslider"},		// Vslider n,n To n,n,n,n,n
	{0x1002,"Set Slider"},	// Set Slider n,n,n,n,n,n,n,n
	{0x1022,"Set Pattern"},
	{0x1034,"Set Line"},
	{0x1044,"Ink"},
	{0x1050,"Ink"},
	{0x105A,"Ink"},		// Ink 0,0,0
	{0x1066,"Gr Writing"},
	{0x1078,"Clip"},
	{0x1084,"Clip"},		// clip x,y To x,y
	{0x10AC,"Set Tempras"},	// Set Tempras addr,length
	{0x10B6,"Appear"},
	{0x10D6,"Zoom"},
	{0x1146,"Get Block"},	// Get Block n,x.y.x.y
	{0x1160,"Get Block"},	// Get Block n,x,y,x,y,n
	{0x1172,"Put Block"},	// Put Block n
	{0x1184,"Put Block"},	// Put Block n,x,y
	{0x11AE,"Del Block"},	// no args
	{0x11BE,"Del Block"},
	{0x11C6,"Key Speed"},
	{0x11D8,"Key State"},
	{0x11E8,"Key Shift"},
	{0x11F8,"Joy"},
	{0x1202,"Jup"},
	{0x120C,"Jdown"},
	{0x1218,"Jleft"},
	{0x1224,"Jright"},
	{0x1232,"Fire"},
	{0x123E,"True"},
	{0x1248,"False"},
	{0x1254,"Put Key"},
	{0x1262,"Scancode"},
	{0x1270,"Scanshift"},
	{0x1280,"Clear Key"},
	{0x1290,"Wait Key"},
	{0x129E,"Wait"},
	{0x12AA,"Key$"},
	{0x12CE,"Timer"},
	{0x12DA,"Wind Open"},
	{0x12F4,"Wind Open"},	// Wind Open n,n, n,n, n,n
	{0x131A,"Wind Close"},
	{0x132A,"Wind Save"},
	{0x133A,"Wind Move"},
	{0x134C,"Wind Size"},
	{0x1378,"Locate"},
	{0x1388,"Clw"},
	{0x1392,"Home"},
	{0x139C,"Curs Pen"},
	{0x13AC,"Pen$"},
	{0x13B8,"Paper$"},
	{0x13C6,"At"},
	{0x13D2,"Pen"},
	{0x13DC,"Paper"},
	{0x13E8,"Centre"},
	{0x13F6,"Border"},
	{0x1408,"Writing"},
	{0x1422,"Title Top"},
	{0x1432,"Title Bottom"},
	{0x1446,"Curs Off"},
	{0x1454,"Curs On"},
	{0x1462,"Inverse Off"},
	{0x1474,"Inverse On"},
	{0x1484,"Under Off"},
	{0x1494,"Under On"},
	{0x14A2,"Shade Off"},
	{0x14B2,"Shade On"},
	{0x14C0,"Scroll Off"},
	{0x14E0,"Scroll"},
	{0x1504,"Cleft$"},
	{0x151E,"Cup"},
	{0x1528,"Cdown"},
	{0x1534,"Cleft"},
	{0x1540,"Cright"},
	{0x154C,"Memorize X"},
	{0x155C,"Memorize Y"},
	{0x157C,"Cmove"},
	{0x158A,"Cline"},
	{0x159E,"Hscroll"},
	{0x15AC,"Vscroll"},
	{0x15BA,"Set Tab"},
	{0x15C8,"Set Curs"},
	{0x15E6,"X Curs"},			// x=X Curs
	{0x15F2,"Y Curs"},			// y=Y Curs
	{0x161E,"Xgr"},			// Xgr
	{0x1628,"Ygr"},			// Ygr
	{0x1632,"Reserve Zone"},	// Reserve Zone n
	{0x1646,"Reserve Zone"},
	{0x164E,"Reset Zone"},		// no args
	{0x1660,"Reset Zone"},
	{0x1668,"Set Zone"},
	{0x1680,"Zone"},		// =Zone( x, y )
	{0x168E,"Zone"},
	{0x16B6,"Scin"},
	{0x16D0,"Mouse Screen"},
	{0x16E2,"Mouse Zone"},
	{0x16F2,"Set Input"},
	{0x1704,"Close Workbecnh"},
	{0x171A,"Close Editor"},
	{0x172C,"Dir First$"},
	{0x173E,"Dir Next$"},
	{0x174E,"Exist"},
	{0x175A,"Dir$"},
	{0x17A4,"Dir"},
	{0x17B6,"Set Dir"},
	{0x17C4,"Set Dir"},		// Set Dir num,fliter$
	{0x17D4,"Load Iff"},	// Load Iff name,num
	{0x17E4,"Load Iff"},
	{0x180C,"Bload"},
	{0x181A,"Bsave"},
	{0x1844,"Save"},
	{0x184E,"Load"},	// Load name$
	{0x185A,"Load"},	// Load name$,num
	{0x1864,"Dfree"},
	{0x1870,"Mkdir"},
	{0x187C,"Lof"},
	{0x1886,"Eof"},
	{0x1890,"Pof"},
	{0x18A8,"Open Random"},
	{0x18BC,"Open In"},
	{0x18CC,"Open Out"},
	{0x18DE,"Open Port"},
	{0x18F0,"Append"},
	{0x1900,"Close"},
	{0x190C,"Close"},
	{0x1914,"Parent"},
	{0x1920,"Rename"},
	{0x1930,"Kill"},
	{0x193C,"Drive"},
	{0x1948,"Field"},
	{0x1954,"Fsel$"},
	{0x196C,"Fsel$"},
	{0x1978,"Fsel$"},
	{0x1986,"Set Sprite Buffer"},
	{0x199E,"Sprite Off"},
	{0x1A10,"Spritebob Col"},
	{0x1A44,"Sprite Col"},	//	=Sprite Col( n,n To n )
	{0x1A72,"Sprite Base"},
	{0x1A84,"Icon Base"},
	{0x1A94,"Sprite"},			// Sprite n,n,n,n
	{0x1AA8,"Bob Off"},
	{0x1AB6,"Bob Off"},		// Bob Off n
	{0x1ABE,"Bob Update Off"},
	{0x1AF6,"Bob Clear"},
	{0x1B06,"Bob Draw"},
	{0x1B14,"Bobsprite Col"},	// Bobsprite Col(n,n To n)
	{0x1B36,"Bob Col"},
	{0x1B52,"Col"},
	{0x1B5C,"Limit Bob"},		// Limit Bob	n,x,y To x,y
	{0x1B6C,"Limit Bob" },
	{0x1B7A,"Limit Bob"},		// Limit Bob	n,x,y To x,y
	{0x1B8A,"Set Bob"},		// Set Bob n,n,n,n
	{0x1B9E,"Bob"},
	{0x1BAE,"Get Sprite Palette"},
	{0x1BC8,"Get Sprite Palette"},	// Get Sprite Palette V1
	{0x1BD0,"Get Sprite"},		// Get Sprite n,x,y To x,y
	{0x1BEA,"Get Sprite" },
	{0x1BFC,"Get Bob"},		// Get Bob n,x,y To x,y
	{0x1C14,"Get Bob"},
	{0x1C26,"Del Sprite" },
	{0x1C38,"Del Sprite" },
	{0x1C42,"Del Bob" },
	{0x1C52,"Del Bob" },
	{0x1C5C,"Del Icon" },
	{0x1C6C,"Del Icon" },
	{0x1C76,"Ins Sprite" },
	{0x1C88,"Ins Bob" },
	{0x1C96,"Ins Icon" },
	{0x1CA6,"Get Icon Palette" },
	{0x1CBE,"Get Icon Palette" },
	{0x1CC6,"Get Icon" },
	{0x1CDE,"Get Icon" },
	{0x1CF0,"Put Bob"},		// Put Bob n
	{0x1CFE,"Paste Bob"},
	{0x1D12,"Paste Icon"},		// Paste Icon n,n,n
	{0x1D28,"Make Mask" },
	{0x1D38,"Make Mask" },
	{0x1D40,"No Mask" },
	{0x1D4E,"No Mask" },
	{0x1D56,"Make Icon Mask" },
	{0x1D6C,"Make Icon Mask" },
	{0x1D74,"No Icon Mask" },
	{0x1D88,"No Icon Mask" },
	{0x1D90,"Hot Spot"},		// Hot Spot x,y
	{0x1DA2,"Hot Spot"},
	{0x1DAE,"Priority On"},
	{0x1DC0,"Priority Off"},
	{0x1DD2,"Hide On"},
	{0x1DE0,"Hide"},
	{0x1DEA,"Show On"},
	{0x1DF8,"Show"},
	{0x1E02,"Change Mouse"},
	{0x1E16,"X Mouse"},
	{0x1E24,"Y Mouse"},
	{0x1E32,"Mouse Key"},
	{0x1E42,"Mouse Click"},
	{0x1E54,"Limit Mouse" },
	{0x1E66,"Limit Mouse" },
	{0x1E6E,"Limit Mouse" },
	{0x1E7C,"Unfreeze" },
	{0x1E8A,"Move X" },
	{0x1E9A,"Move X" },
	{0x1EA6,"Move Y" },
	{0x1EB6,"Move Y" },
	{0x1EC2,"Move Off" },
	{0x1ED2,"Move Off" },
	{0x1EDA,"Move On" },
	{0x1EE8,"Move On" },
	{0x1EF0,"Move Freeze" },
	{0x1F02,"Move Freeze" },
	{0x1F0A,"Anim Off" },
	{0x1F1A,"Anim Off" },
	{0x1F22,"Anim On" },
	{0x1F30,"Anim On" },
	{0x1F38,"Anim Freeze" },
	{0x1F4A,"Anim Freeze" },
	{0x1F52,"Anim" },
	{0x1F60,"Anim" },
	{0x1F6C,"Movon" },
	{0x1F78,"Chanan" },
	{0x1F86,"Chanmv"},	// Chanmv(a)
	{0x1F94,"Channel"},
	{0x1FA2,"Amreg"},		// Amreg(a)
	{0x1FB0,"Amreg"},		// Amreg(a,b)
	{0x1FBC,"Amal On"},	
	{0x1FCA,"Amal On"},
	{0x1FD2,"Amal Off"},	// no args
	{0x1FE2,"Amal Off"},
	{0x1FEA,"Amal Freeze"},
	{0x1FFC,"Amal Freeze"},	// Amal Freeze n
	{0x2004,"Amalerr"},
	{0x2012,"Amal"},
	{0x2020,"Amal"},	// Amal num,str to num
	{0x202C,"Amplay" },
	{0x203C,"Amplay" },
	{0x204A,"Synchro On"},
	{0x205A,"Synchro Off"},
	{0x206C,"Synchro"},
	{0x207A,"Update Off"},
	{0x208A,"Update On" },
	{0x209A,"Update Every"},	// Update Every v1
	{0x20AE,"Update"},
	{0x20BA,"X Bob"},
	{0x20C6,"Y Bob"},
	{0x20D2,"X Sprite"},
	{0x20E2,"Y Sprite"},
	{0x20F2,"Reserve As Work"},
	{0x210A,"Reserve As Chip Work"},
	{0x2128,"Reserve As Data"},
	{0x2140,"Reserve As Chip Data"},
	{0x215E,"Erase"},
	{0x216A,"List Bank"},
	{0x217A,"Chip Free"},
	{0x218A,"Fast Free"},
	{0x219A,"Fill"},
	{0x21AA,"Copy"},
	{0x21BA,"Hunt" },
	{0x21CA,"Poke"},
	{0x21D8,"Loke"},
	{0x21E6,"Peek"},
	{0x21F2,"Deek"},
	{0x21FE,"Leek"},
	{0x220A,"Bset"},
	{0x2218,"Bclr"},
	{0x2226,"Bchg"},
	{0x2234,"Btst"},
	{0x2242,"Ror.b" },
	{0x2250,"Ror.w" },
	{0x225E,"Ror.l" },
	{0x226C,"Rol.b" },
	{0x227A,"Rol.w" },
	{0x2288,"Rol.l" },
	{0x2296,"Areg"},
	{0x22A2,"Dreg"},
	{0x22AE,"Copper On"},
	{0x22BE,"Copper Off" },
	{0x22CE,"Cop Swap" },
	{0x22DC,"Cop Reset" },
	{0x22EC,"Cop Wait" },
	{0x22FE,"Cop Wait" },
	{0x230C,"Cop Movel" },
	{0x231E,"Cop Move" },
	{0x2330,"Cop Logic" },
	{0x2340,"Prg First$" },
	{0x2352,"Prg Next$" },
	{0x2362,"Psel$" },
	{0x2370,"Psel$" },
	{0x237A,"Psel$" },
	{0x2386,"Psel$" },
	{0x2394,"Prun"},
	{0x23A0,"Bgrab" },
	{0x23AC,"Put"},
	{0x23B8,"Get"},
	{0x23C4,"System"},
	{0x23D0,"Multi Wait"},
	{0x23E0,"I Bob"},
	{0x23EC,"I Sprite" },
	{0x23FC,"Priority Reverse On"},
	{0x2416,"Priority Reverse Off"},
	{0x2430,"Dev First$"},
	{0x2442,"Dev Next$"},
	{0x2452,"Hrev Block"},	// Hrev Block n
	{0x2464,"Vrev Block"},	// Vrev Block n
	{0x2476,"Hrev"},		// =Hrev(n)
	{0x2482,"Vrev"},		// =Vrev(n)
	{0x248E,"Rev"},
	{0x2498,"Bank Swap"},
	{0x24AA,"Amos To Front"},
	{0x24BE,"Amos To Back "},
	{0x24D0,"Amos Here" },
	{0x24E0,"Amos Lock"},
	{0x24F0,"Amos Unlock"},
	{0x2502,"Display Height" },
	{0x2516,"Ntsc"},
	{0x2520,"Laced"},
	{0x252C,"Prg State"},
	{0x253C,"Command Line$"},
	{0x2550,"Disc Info$"},
	{0x2578,"Set Accessory"},
	{0x259A,"Trap"},
	{0x25C0,"Array"},
	{0x25CC,"Frame Load"},
	{0x25E0,"Frame Load"},		//	Frame Load(n To n,n)
	{0x25EC,"Frame Play"},		//	Frame Play n,n
	{0x2600,"Frame Play"},		//	Frame Play n,n,n
	{0x260C,"Iff Anim" },
	{0x261E,"Iff Anim" },
	{0x262A,"Frame Length"},	//	Frame Length(n)
	{0x263E,"Frame Length"},	//	Frame Length(n,n)
	{0x2664,"Wait Frame"},		//	Wait Frame n
	{0x2676,"Call Editor"},		//	Call Editor n
	{0x268A,"Call Editor"},		//	Call Editor n,n
	{0x2694,"Call Editor"},		//
	{0x26A0,"Ask Editor" },
	{0x26B2,"Ask Editor" },
	{0x26BC,"Ask Editor" },
	{0x26C8,"Erase Temp" },
	{0x26D8,"Erase All" },
	{0x26E8,"Dialog Box" },
	{0x26FA,"Dialog Box" },
	{0x2704,"Dialog Box" },
	{0x2710,"Dialog Box" },
	{0x2720,"Dialog Open"},
	{0x2736,"Dialog Open"},		//	Dialog Open n,n,n
	{0x2742,"Dialog Open"},		//	Dialog Open n,n,n,n
	{0x2750,"Dialog Close"},	//	Dialog Close  --- No args
	{0x2764,"Dialog Close"},
	{0x276C,"Dialog Run" },
	{0x277E,"Dialog Run" },
	{0x2788,"Dialog Run" },
	{0x2796,"Dialog" },
	{0x27A4,"Vdialog" },
	{0x27B6,"Vdialog$" },
	{0x27C8,"Rdialog" },
	{0x27DA,"Rdialog" },
	{0x27E6,"Rdialog$" },
	{0x27F8,"Rdialog$" },
	{0x2804,"Edialog"},
	{0x2812,"Dialog Clr"},		//	Dialog Clr n
	{0x2824,"Dialog Update"},
	{0x283C,"Dialog Update"},	//	Dialog Update n,n,n
	{0x2848,"Dialog Update"},	//	Dialog Update n,n,n,n
	{0x2856,"Dialog Update"},	//	Dialog Update n,n,n,n,n
	{0x2866,"Dialog Freeze"},
	{0x287A,"Dialog Freeze"},
	{0x2882,"Dialog Unfreeze"},
	{0x2898,"Dialog Unfreeze"},
	{0x28A0,"Poke$"},
	{0x28AE,"Peek$"},
	{0x28BE,"Peek$"},
	{0x28CA,"Resource Bank"},
	{0x28DE,"Resource$"},
	{0x28EE,"Resource Screen Open"},		// Resource Screen Open number,width,height,flash
	{0x2910,"Resource Unpack"},			// Resource Unpack n,n
	{0x292A,"Read Text"},
	{0x2946,"Err$" },
	{0x2952,"Assign" },
	{0x2962,"Errtrap" },
	{0x2970,"Dev Open" },
	{0x2988,"Dev Close" },
	{0x2998,"Dev Close" },
	{0x29A0,"Dev Base" },
	{0x29B0,"Dev Do" },
	{0x29C0,"Dev Send" },
	{0x29D2,"Dev Abort" },
	{0x29E2,"Dev Check" },
	{0x29F2,"Lib Open" },
	{0x2A06,"Lib Close" },
	{0x2A16,"Lib Close" },
	{0x2A1E,"Lib Call" },
	{0x2A30,"Lib Base" },
	{0x2A40,"Equ" },
	{0x2A4A,"Lvo" },
	{0x2A54,"Struc" },
	{0x2A64,"Struc$" },
	{0x2A74,"Bstart" },
	{0x2A82,"Blength" },
	{0x2A90,"Bsend" },
	{0x2A9C,"Bank Shrink" },
	{0x2AB0,"Prg Under"},
	{0x2AC0,"Arexx Open"},
	{0x2AD2,"Arexx Close"},
	{0x2AE4,"Arexx Exist"},
	{0x2AF6,"Arexx"},
	{0x2B02,"Arexx$"},			// = Arexx$( n )
	{0x2B10,"Arexx Wait"},
	{0x2B20,"Arexx Answer" },
	{0x2B34,"Arexx Answer" },
	{0x2B3E,"Exec" },
	{0x2B4A,"Monitor" },
	{0x2B58,"Screen Mode" },
	{0x2B6A,"Screen Mode" },
	{0x2B72,"Kill Editor" },
	{0x2B84,"Set Double Precision" },
	{0x2B9E,"Set Stack" },
	{0x2BAE,"Get Bob Palette" },
	{0x2BC4,"Get Bob Palette" },
	{0x2BCC,"Set Equate Bank" },
	{0x2BE2,"Zdialog" },
	{0xFF4C,"or"},
	{0xFF58,"and"},
	{0xFFD4,"mod"}
};

BOOL findSymbol(unsigned short token)
{
	struct nativeCommand *ptr;
	int size = sizeof(Symbol)/sizeof(struct nativeCommand);

	for (ptr =Symbol ; ptr < Symbol + size ; ptr++ )
	{
		if (token == ptr->id ) 
		{
			if ((token == 0xFFCA)&&(space_after ==' ')) printf(" ");

			if (token == 0xFFA2) equal_symbol = TRUE;
			space_after = 0;

			printf("%s", ptr -> name);
			return TRUE;
		}
	}
	return FALSE;
}



BOOL findNativeCommand(unsigned short lastToken, unsigned short token)
{
	struct nativeCommand *ptr;
	int size = sizeof(NativeCommand)/sizeof(struct nativeCommand);

	for (ptr =NativeCommand ; ptr < NativeCommand + size ; ptr++ )
	{
		if (token == ptr->id ) 
		{
			if (
				(last_token_is==is_var)||
				(last_token_is==is_label)||
				(last_token_is==is_string)||
				(last_token_is==is_number)||
				(last_token_is==is_command)||
				(lastToken == 0x007C)				// symbol ")"
			) printf(" ");

			printf("%s", ptr -> name);

//			equal_symbol = FALSE;

			return TRUE;
		}
	}
	return FALSE;
}
