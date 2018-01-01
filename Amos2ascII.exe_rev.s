VERSION = 1
REVISION = 1

.macro DATE
.ascii "1.1.2018"
.endm

.macro VERS
.ascii "Amos2ascII.exe 1.1"
.endm

.macro VSTRING
.ascii "Amos2ascII.exe 1.1 (1.1.2018)"
.byte 13,10,0
.endm

.macro VERSTAG
.byte 0
.ascii "$VER: Amos2ascII.exe 1.1 (1.1.2018)"
.byte 0
.endm
