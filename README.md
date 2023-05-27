# _amiga-debug_ Visual Studio Code Extension (fork with libraries support)

This fork is based on the marvellous vscode-amiga-debug extension [vscode-amiga-debug by Bartman^Abyss](https://marketplace.visualstudio.com/items?itemName=BartmanAbyss.amiga-debug), which is also available on [github](https://github.com/BartmanAbyss/vscode-amiga-debug).

![screen-mui](screen_mui.png)

## Additional features

- Standard Amiga libraries are available (you need to specify a Workbench floppy disk or hard disk; see below).
- MUI is also included on the compilation side (SDK v3.9) and on the execution side (libraries v3.8).
- Custom libraries can be declared through the setting of assigns.
- The bsdsocket.library of UAE can also be enabled.
- Equivalent of amiga.lib, alib (from https://github.com/jyoberle/alib), is included.
- Additional commands to be added at the end of the startup-sequence can be specified.
	
## Quick-start
0. Install the extension from the Visual Studio Code Marketplace
1. Create a new empty project folder with `File > Open Folder...`
2. From the command palette <kbd>Ctrl+Shift+P</kbd> select `Amiga: Init Project With Libs`
3. Open `.vscode/launch.json` and make `"kickstart"` point to your *Kickstart 3.1* ROM and `"workbench"` to your *Workbench 3.1* floppy (.adf)
4. Hit <kbd>F5</kbd> to build and run a minimal sample project (you should see the MUI app of the above screenshot)
5. You'll also find on youtube a [video showing the previous steps](https://www.youtube.com/watch?v=qjIraPFSK_c).

## How-to-use
- In `.vscode/launch.json`, you can also make `"workbench"` point to a hard file (.hdf) containing the *Workbench 3.1*; in this case, for WinUAE, you need to specify at the end of its path its number of sectors, number of surfaces,
 number of reserved blocks, and block size (e.g. "workbench": "C:/Path to hard file/A1200.hdf,32,1,2,512") as they appear in the settings window of WinUAE (see picture below). For FS-UAE, just specify the path to the .hdf file
 (e.g. "workbench": "C:/Path to hard file/A1200.hdf").
- Both for WinUAE and FS-UAE, you can also make `"workbench"` point to a directory virtual hard disk (e.g. "workbench": "C:/Path to  directory virtual hard disk/A1200_dir").
- Still in `.vscode/launch.json`, you can specify with `"assigns"` a list of assigns (separated by commas) which will be translated in the startup-sequence; for example "assigns":"MUI: DH2:MUI,LIBS: DH2:LIBS DH2:MUI/Libs" will
 add at the end of the startup-sequence:<br />
assign MUI: DH2:MUI<br />
assign LIBS: DH2:LIBS DH2:MUI/Libs<br />
The purpose is to add the ability to declare your own libraries residing on your hard file or directory virtual hard disk. These latest are defined as DH2: (DH0: is a directory virtual hard drive, used for booting and where the
 startup-sequence is located, and DH1: is the directory virtual hard drive containing your compiled program). Thus, the content of DH2: is never modified.
- `"bsdSocket"` can be set to true (e.g. "bsdSocket":true) to enable the bsdsocket.library of UAE.
- At last, with `"cmdList"`, you can specify a list of commands (separated by commas) which will be added at the end of the startup-sequence, e.g. "cmdList":"df0:System/rexxmast".

![UAE_HardFile](screen_uae_hardfile.png)

## How does it work?
- This fork has the MUI libraries included in the disk DH0: which is already used by the original vscode-amiga-debug extension to store the startup-sequence and to boot the Amiga.
- It adds the needed definitions to the UAE configuration file to declare your `"workbench"` pointing to a floppy, a hard file or a directory virtual hard disk, and to enable optionally the bsdsocket.library.
- It also adds the following instructions to the startup-sequence (when `"workbench"` points to a hard file or a directory virtual hard disk; for a floppy disk, just replace DH2: by DF0:):<br />
DH2:C/assign C: DH2:C<br />
C:assign SYS: DH2:<br />
C:assign S: DH2:S<br />
C:assign LIBS: DH2:LIBS DH0:MUI/Libs<br />
C:assign DEVS: DH2:Devs<br />
C:assign FONTS: DH2:Fonts<br />
C:assign L: DH2:L<br />
C:MakeDir RAM:T RAM:Clipboards RAM:ENV RAM:ENV/Sys<br />
C:assign T: RAM:T<br />
C:assign CLIPS: RAM:Clipboards<br />
C:assign ENV: RAM:ENV<br />
C:assign LOCALE: DH2:Locale dh0:MUI/Locale<br />
C:assign PRINTERS: DEVS:Printers<br />
- At last, when you define `"assigns"`, it adds your assigns at the end of the startup-sequence (see above for an example). And in case you define additional commands with `"cmdList"`, they are also added at the end of the startup-sequence.

## Change Log (fork only)

### 1.7.2
- Equivalent of amiga.lib, alib (from https://github.com/jyoberle/alib), included
- Added the ability to specify additional commands for the startup-sequence

### 1.7.1
- Added the ability to use a directory virtual hard disk for the workbench

### 1.6.8
- Support for libraries

## Additional credits

- Code by [JOB](https://github.com/jyoberle).

- Magic User Interface (MUI) is Copyright (C) 1992-2013 by Stefan Stuntz. Version 3.9 can be downloaded from https://github.com/amiga-mui/muidev/releases/tag/MUI-3.9-2015R1. Installation of version 3.8 is described
 on https://guide.abime.net/wb3.1/chap6.htm.
 
- Some portions of the example code are inspired by AROS code (https://github.com/aros-development-team/AROS).
