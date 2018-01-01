VERSION		EQU	1
REVISION	EQU	1

DATE	MACRO
		dc.b '1.1.2018'
		ENDM

VERS	MACRO
		dc.b 'Amos2ascII.exe 1.1'
		ENDM

VSTRING	MACRO
		dc.b 'Amos2ascII.exe 1.1 (1.1.2018)',13,10,0
		ENDM

VERSTAG	MACRO
		dc.b 0,'$VER: Amos2ascII.exe 1.1 (1.1.2018)',0
		ENDM
