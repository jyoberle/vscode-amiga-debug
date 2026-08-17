If you are reading this file, it means that you successfully created the example project. Congratulations!

1. Running the example project (Amiga OS 3.1)
=============================================

This example project is configured to compile and run a MUI program under Amiga OS 3.1. You still have two steps to reach this goal:
a) In the file .vscode/launch.json (for example for the Amiga 500), fill the entry "kickstart" with a path to a kickstart 3.1 ROM file, e.g.: "kickstart": "C:/amiga/kick3.1.rom"
Please be sure to use paths without spaces.
b) Then fill the "workbench" entry with a path to a Workbench 3.1 ADF file, for example "workbench": "C:/amiga/workbench3.1.adf"

Finally, press F5. These steps are detailed in my youtube video: https://youtu.be/qjIraPFSK_c.

2. Running the second example project (Amiga OS 3.2)
====================================================

If you want to run the example designed for Amiga OS 3.2, a few new steps are required:
a) First, create an installation of Amiga OS 3.2 on a directory virtual hard disk inside WinUAE/FS-UAE, for an Amiga 1200. The following video gives all the details for this step: https://www.youtube.com/watch?v=XKnSbTQDI_o.
But please, unlike shown in the video, rather use a directory virtual hard disk instead of a hardfile (click on "Add Directory or Archive..." instead of "Add Hardfile..." in "CD & "Hard drives" menu)
b) As before, in .vscode/launch.json, but this time in the Amiga 1200 section, fill "kickstart" and "workbench", e.g. "kickstart": "C:/amiga/kicka1200.rom" and "workbench": "C:/amiga/A1200_3.2_vdd" (note the latest virtual disk)
c) In the Makefile, change the SDKDIR path to point to ndk-include instead of sys-include (you can comment the old SDKDIR line and uncomment the new one)
d) In the l_option.h file, set both OPTION_USE_CLIB2 and OPTION_AMIGA_OS32 to 1:
#define OPTION_USE_CLIB2 1
#define OPTION_AMIGA_OS32 1
e) To ensure the full example is recompiled, clean the project by pressing Ctrl+P and type "task clean"

Everything is now ready for the OS 3.2 example: press again Ctrl+P and type "debug Amiga 1200" to compile and run it. It will open the MUI window and then run four programs coming from the OS 3.2 NDK (bevels, buttons, checkbox and requester).

3. Using the environment for your own developments
==================================================

Whether you decide to use this environment to develop programs for OS 3.1 or 3.2, you can tailor it to fit your needs.

For example, the startup-sequence can be modified and simplified to speed up the boot.

If you are planning to use the clib2 libraries in your project, your code can rely on the skeleton of the main.c file (see below for more details).

You'll also find in the misc.c file some functions of the Amiga libraries (NewObject, MUI_MakeObject, etc.) which have been rewritten to be compatible with modern gcc.
Since these few functions should not come from the Amiga libraries but from the misc.c file, includes involving intuition.h should be surrounded by NO_INLINE_STDARG:
#define NO_INLINE_STDARG
#include <proto/intuition.h>
#undef NO_INLINE_STDARG
Also all includes of pragmas should be replaced by their equivalent proto includes, e.g.:
#include <pragmas/label_pragmas.h>
#include <pragmas/layout_pragmas.h>
#include <pragmas/window_pragmas.h>
translated to:
#include <proto/label.h>
#include <proto/layout.h>
#include <proto/window.h>
You'll find examples of this practice in the Bevels.c, Buttons.c, CheckBox.c and Requester.c files.

4. Using clib2
==============

clib2 provides a set of static libraries (stdlib, stdio, amigalib, etc.) which are useful to the C programmer.
You can do a minimal test of clib2 by setting OPTION_TEST_CLIB to 1 in the l_option.h file (both for Amiga OS 3.1 and 3.2).
Please refer to https://github.com/jyoberle/clib2 for all details about clib2.

If you want to use the clib2 libraries in your own project, your code will have to follow the skeleton of the main.c file.

It is also mandatory:
- To declare the static libs in your Makefile:
a. static_libs := -lc -lm -ldebug -lnet -lunix -lc -lm -lamiga, to use Amiga style paths, or
b. static_libs := -lm -ldebug -lnet -lunix -lc -lm -lamiga, to use UNIX style paths (e.g. "/RAM/myfile" instead of "RAM:myfile")
- To call SetPatch in your startup-sequence
- To increase the stack size (to 16384 bytes), especially if you use libunix
- To mount the PIPE: device (only required for Amiga OS 3.1) if you intend to use pipe functions (popen, pclose, etc.)
- To have the bsdsocket.library installed in your system (it is required by libnet); this is done in .vscode/launch.json file through the instruction "bsdSocket":true
- To have AmiTCP installed in your system if you want to take full advantage of the usergroup functions (like setuid, setgroups, etc.)
- To NOT use libnet functions and native bsdsocket.library functions together, as they are incompatible; in order to avoid this, do not include "<inline/bsdsocket.h>" in your code if your intention is to use libnet
 
Please be also aware of the current limitations of clib2:
- libm881 has not been tested and is provided as-is
- ARexx functions GetRexxVar and SetRexxVar are not yet working in the current version of libamiga
- Neither 64 bits integers nor long double are supported
- The following functions are currently do-nothing: feclearexcept, fegetenv, fegetexceptflag, fegetround, feholdexcept, feraiseexcept, fesetenv, fesetexceptflag, fetestexcept, fetestround, feupdateenv

You'll find some examples on how to use the clib2 functions in https://github.com/jyoberle/clib2.

5. Using RTG
============

If your future programs require the use of RTG (retargetable graphics) mode, it is possible to configure the extension to start WinUAE/FS-UAE in this mode. Again, there are a few steps to achieve this goal:
a) First, you'll have to configure your OS 3.1 or 3.2 for RTG. All steps are detailed in this video: https://www.youtube.com/watch?v=2ENWAMajvjQ. 
For the next steps, we will take the assumption that you have configured a kickstart and Workbench for Amiga 1200 (68020 processor), like in the video
b) Back in Visual Studio code, set the "config" as "A1200-RTG" :
"config": "A1200-RTG"
c) Then, in the launch.json file, specify width and height with the same values as the ones you used to configure the resolution of the display mode in WinUAE/FS-UAE (640 x 480 in the video):
"width":"640",
"height":"480"
d) Optionally, you can also specify that you want to start in fullscreen mode:
"fullscreen":true

After this setup, compilation is started as usual by pressing F5.

6. Compiling with GCC 13.2
==========================

GCC 15.2 (and above) is more restrictive regarding C coding rules (your old code may break). For this reason, the extension allows you to still use version 13.2. To force your project to use GCC 13.2:
a) Edit the Visual Studio Code settings (press Ctrl + ,), navigate to Extensions -> Amiga C/C++ Compile, Debug & Profile, and set "Amiga: Gcc Version" to "13.2",
b) Or create a .vscode/settings.json file with:
{
  "amiga.gccVersion": "13.2"
}

Set the "Amiga: Gcc Version" setting or "amiga.gccVersion" property to an empty string ("") if you want to switch back to GCC 15.2 (do not specify "15.2"!). Don't forget to clean the project (press Ctrl+P and type "task clean") when switching between GCC versions.

7. A few words to conclude
==========================

At last, to take fully advantage of this extension, if not already done, you can read the guidelines in https://github.com/jyoberle/vscode-amiga-debug.

And to finish, I wish you a warm welcome to the marvellous world of modern Amiga development!