# Amos2AscII
Translate Token AMOS Source code into ASCII Source code

Amos2AscII works as Amiga Icon tool, can started just clicking on it, or from shell.

Declaimer:
----------
Amos2AscII is work in progress. Not all commands are supported by the program.


About this program:
-------------------
It has been suggested that commands can be extracted from lib files, while that might be possible I don't know the format of this files.

I have some idea that at 0x20 in file there size of code some data stored. That get close the commands file offset, but what, beyond this I know all commands in .lib files have bit 7 set, at end of the command, and next bytes is 0xFF, there is kind of 16 bit alignment, but I'm not sure about where to align. Then 4 to 6 bytes so to next command, some time there are some parameter in between. 

Anyway, I do not have time to speculate about it, and come long way at documenting the tokens I run into. Because AMOS Pro is no longer commercial product, I will not expect any new commands, being added to language, and so need to dynamically read the files might not be so essential. But if you feel like it study the files fork this project and make the changes, that’s what Open Source is all about is not.
Anyway this project kind a started due lack of sources and information about AMOS was bad, but was not excellent, there were not any examples. Therefore, I guess that is my main motivation for this project, besides being able to view Amos source code on AmigaOS4.1 without aid of emulation.

My hope here that this project my fork into other projects like AMOS token editors, transcoders AMOS to C, AMOS interpreters and so on. So project might start or seed in documenting AMOS, to maybe give it new life.

Amos was good beginner's language; it feels like half of my life is in Amos. This is way AMOS has this emotional value to me, and way I think maybe It's worth spending some time on it.
