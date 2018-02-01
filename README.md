# Amos2AscII
Translate Token AMOS Source code into ASCII Source code

Amos2AscII works as Amiga Icon tool, can started just clicking on it, or from shell.

What heck is this?
------------------
Amos or Amos Profersonal, also know as "Amos the creator", is a basic lanuage dialect. 
The language was first developed for Atari at time it was called STOS, then development continued on 
Amiga computers, AMOS/STOS is creation of "Francois Lionet".

Sadly development of language stopped no updates for AGA graphics or CGX/P96. When language was developed, 
there was lack of space on floppy disks, there were no drivers, there was lack of gadgets/widgets, 
and graphic library's to help aid developers, AMOS made development easy, compared to learning assembler,
and it lot faster than other Basic versions when it was released. 

I not sure way but AMOS does not use ASCII for source code, it used binary format,
where etch command is encoded as a hex dismal unsigned short or uint16 if you like.
Some tokens have additional flags or options, or data that is attached to it.

This tool is excellent for converting AMOS Pro code to ASCII, is also excellent for debugging,
as tool as additional option to show tokens and data, it also be used extract ABK file from AMOS source code,
ABK is like archive that can contain samples, images, sprites, icons, menus and lots more.

You can also use this tool if AMOS pro refuses to load AMOS file, because it corrupted or not complete,
this tool does not care, if you have half of a file or complete file.

About this program:
-------------------
If you feel like it study the files fork this project and make the changes, that's what Open Source is all about is not.
Anyway this project kind a started due lack of sources and information about AMOS was bad, but was not excellent, there were not any examples. Therefore, 
I guess that is my main motivation for this project, besides being able to view Amos source code on AmigaOS4.1 without aid of emulation.

My hope here that this project my fork into other projects like AMOS token editors, transcoders AMOS to C++, 
AMOS interpreters and so on. So project might start or seed in documenting AMOS, to maybe give it new life.

Amos was good beginner's language; it feels like half of my life is in Amos. This is way AMOS has this emotional value to me, and way I think maybe It's worth spending some time on it.

Dependences
-----------
This program uses AmosExtension.library to obtain Command names from Amos extensions.

program will try to read config file from this paths, in this coder.

1. <path to .amos file>/AMOSPro_Interpreter_Config
2. amospro:s/AMOSPro_Interpreter_Config
3. s:AMOSPro_Interpreter_Config
4. progdir:AMOSPro_Interpreter_Config

program will try the next until it find it.

Unlike AmosPro this program look for AMOSPro_Interpreter_Config in <path to .amos file>,
this is because, *.AMOS token files might not use the same extensions, and mismatch between 
extensions is possible between source codes. amospro:s is next logical place if your read of ADF image or floppy disk.
s: if its installed to HD, and progrdir if AMOSPRO is not found, in this case it fail to load extensions ;-), 
because it wont be able to find any.

Orginal source code can be found here:
--------------------------------------
https://github.com/khval/Amos2AscII
