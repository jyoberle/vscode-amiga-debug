#include <proto/exec.h>
#include <proto/intuition.h>
#define NO_INLINE_STDARG
#include <proto/muimaster.h>
#undef NO_INLINE_STDARG
#include <proto/utility.h>
#include <proto/icon.h>
#include <clib/alib_protos.h>
#include "g_misc.h"

#define MUI_LIB_VERSION 19L

// We need to declare the libraries as "externally_visible" since we are using the option -fwhole-program in the Makefile
__attribute__((externally_visible)) struct ExecBase *SysBase;
__attribute__((externally_visible)) struct IntuitionBase *IntuitionBase = NULL;
__attribute__((externally_visible)) struct DosLibrary *DOSBase = NULL;
__attribute__((externally_visible)) struct UtilityBase *UtilityBase = NULL;
__attribute__((externally_visible)) struct GfxBase *GfxBase = NULL;
__attribute__((externally_visible)) struct Library *CxBase = NULL;
__attribute__((externally_visible)) struct Library *IconBase = NULL;
struct Library *MUIMasterBase = NULL;

// This function is based on the MUI example "ShowHide" which can be downloaded from https://github.com/amiga-mui/muidev/releases/tag/MUI-3.9-2015R1
void MUIShowHide(void)
{
	Object *app,*window,*cm1,*cm2,*cm3,*cm4,*cm5,*bt1,*bt2,*bt3,*bt4,*bt5;

	app = ApplicationObject,
		MUIA_Application_Title      , "ShowHide",
		MUIA_Application_Version    , "$VER: ShowHide 20.172 (07.02.2009)",
		MUIA_Application_Copyright  , "(C) 1992-2006 Stefan Stuntz",
		MUIA_Application_Author     , "Stefan Stuntz",
		MUIA_Application_Description, "Show object hiding.",
		MUIA_Application_Base       , "SHOWHIDE",

		SubWindow, window = WindowObject,
			MUIA_Window_Title, "Show & Hide",
			MUIA_Window_ID   , MAKE_ID('S','H','H','D'),

			WindowContents, HGroup,

				Child, VGroup, GroupFrame,

					Child, HGroup, MUIA_Weight, 0,
						Child, cm1 = CheckMark(TRUE),
						Child, cm2 = CheckMark(TRUE),
						Child, cm3 = CheckMark(TRUE),
						Child, cm4 = CheckMark(TRUE),
						Child, cm5 = CheckMark(TRUE),
						End,

					Child, VGroup,
						Child, bt1 = SimpleButton("Button 1"),
						Child, bt2 = SimpleButton("Button 2"),
						Child, bt3 = SimpleButton("Button 3"),
						Child, bt4 = SimpleButton("Button 4"),
						Child, bt5 = SimpleButton("Button 5"),
						Child, VSpace(0),
						End,

					End,
				End,
			End,
		End;
	
	DoMethod(window,MUIM_Notify,MUIA_Window_CloseRequest,TRUE,
		app,2,MUIM_Application_ReturnID,MUIV_Application_ReturnID_Quit);

	DoMethod(cm1,MUIM_Notify,MUIA_Selected,MUIV_EveryTime,bt1,3,MUIM_Set,MUIA_ShowMe,MUIV_TriggerValue);
	DoMethod(cm2,MUIM_Notify,MUIA_Selected,MUIV_EveryTime,bt2,3,MUIM_Set,MUIA_ShowMe,MUIV_TriggerValue);
	DoMethod(cm3,MUIM_Notify,MUIA_Selected,MUIV_EveryTime,bt3,3,MUIM_Set,MUIA_ShowMe,MUIV_TriggerValue);
	DoMethod(cm4,MUIM_Notify,MUIA_Selected,MUIV_EveryTime,bt4,3,MUIM_Set,MUIA_ShowMe,MUIV_TriggerValue);
	DoMethod(cm5,MUIM_Notify,MUIA_Selected,MUIV_EveryTime,bt5,3,MUIM_Set,MUIA_ShowMe,MUIV_TriggerValue);

	set(cm3,MUIA_Selected,FALSE);

/*
** This is the ideal input loop for an object oriented MUI application.
** Everything is encapsulated in classes, no return ids need to be used,
** we just check if the program shall terminate.
** Note that MUIM_Application_NewInput expects sigs to contain the result
** from Wait() (or 0). This makes the input loop significantly faster.
*/

	set(window,MUIA_Window_Open,TRUE);

	{
		ULONG sigs = 0;

		while ((LONG)DoMethod(app,MUIM_Application_NewInput,&sigs) != MUIV_Application_ReturnID_Quit)
		{
			if (sigs)
			{
				sigs = Wait(sigs | SIGBREAKF_CTRL_C);
				if (sigs & SIGBREAKF_CTRL_C) break;
			}
		}
	}

	set(window,MUIA_Window_Open,FALSE);
}

// Does the clean up of all ressources
void cleanUP(void)
{
	if(IntuitionBase != NULL)
		CloseLibrary((struct Library *)IntuitionBase);

	if(DOSBase != NULL)
		CloseLibrary((struct Library *)DOSBase);

	if(UtilityBase != NULL)
		CloseLibrary((struct Library *)UtilityBase);

	if(GfxBase != NULL)
		CloseLibrary((struct Library *)GfxBase);

	if(CxBase != NULL)
		CloseLibrary(CxBase);

	if(IconBase != NULL)
		CloseLibrary(IconBase);

	if(MUIMasterBase != NULL)
		CloseLibrary(MUIMasterBase);
}

// We need to redefine some MUI functions because gcc, due to optimisations, is not always pushing all tags on the stack
Object *MUI_NewObject(CONST_STRPTR cl, Tag tags, ...)
{
	Object *ret = NULL;
	va_list param;
	struct TagItem *tagItem;

	va_start(param,tags);

	if((tagItem = CopyTagsToMem(tags,param))) 
	{
		ret = MUI_NewObjectA(cl,(struct TagItem *)tagItem);
		FreeTagMem(tagItem);
	}

	va_end(param);

	return(ret);
}

Object *MUI_MakeObject(LONG type,...)
{
	Object *ret = NULL;
	va_list param;
	Tag firstTag;
	struct TagItem *tagItem;

	va_start(param,type);
	firstTag = (Tag)va_arg(param,Tag);

	if((tagItem = CopyTagsToMem(firstTag,param))) 
	{
		ret = MUI_MakeObjectA(type,(ULONG *)tagItem);
		FreeTagMem(tagItem);
	}

	va_end(param);

	return(ret);
}

LONG MUI_Request(APTR app,APTR win,ULONG flags,CONST_STRPTR title,CONST_STRPTR gadgets,CONST_STRPTR format,...)
{
	LONG ret = 0L;

	va_list param;
	Tag firstTag;
	struct TagItem *tagItem;

	va_start(param,format);
	firstTag = (Tag)va_arg(param,Tag);

	if((tagItem = CopyTagsToMem(firstTag,param))) 
	{
		ret = MUI_RequestA(app,win,flags,title,gadgets,format,tagItem);
		FreeTagMem(tagItem);
	}

	va_end(param);

	return(ret);
}

APTR MUI_AllocAslRequestTags(unsigned long reqType, Tag Tag1, ...)
{
	APTR ret = NULL;
	va_list param;
	struct TagItem *tagItem;

	va_start(param,Tag1);

	if((tagItem = CopyTagsToMem(Tag1,param))) 
	{
  		ret = MUI_AllocAslRequest(reqType,(struct TagItem *)tagItem);
		FreeTagMem(tagItem);
	}

	va_end(param);
  	
	return(ret);
}

BOOL MUI_AslRequestTags(APTR requester, Tag Tag1, ...)
{
	BOOL ret =  FALSE;
	va_list param;
	struct TagItem *tagItem;

  	va_start(param,Tag1);

	if((tagItem = CopyTagsToMem(Tag1,param))) 
	{
		ret = MUI_AslRequest(requester,(struct TagItem *)tagItem);
		FreeTagMem(tagItem);
	}

	va_end(param);

	return(ret);
}

// Entry of our code
int main(int argc, char **argv) 
{
	SysBase = *((struct ExecBase**)4UL);
	struct Process *proc;
	struct WBStartup *wbmsg = NULL;

	// We check if our program has been started by the workbench or by the shell
	if (argc == 0) {
		// We have been launched by workbench: we wait for the startup message
		proc = (struct Process *)FindTask(NULL);
		WaitPort(&proc->pr_MsgPort);
		wbmsg = (struct WBStartup *)GetMsg(&proc->pr_MsgPort);
	}

	// We open the libraries (required since we are linking with alib; please see https://github.com/jyoberle/alib for details)
	IntuitionBase = (struct IntuitionBase *)OpenLibrary((CONST_STRPTR)"intuition.library",0L);
	DOSBase = (struct DosLibrary *)OpenLibrary((CONST_STRPTR)"dos.library",0L);
	UtilityBase = (struct UtilityBase *)OpenLibrary((CONST_STRPTR)"utility.library",0L);
	GfxBase = (struct GfxBase *)OpenLibrary("graphics.library",0);
	CxBase = OpenLibrary("commodities.library",0);
	IconBase = OpenLibrary("icon.library",0);
	MUIMasterBase = OpenLibrary("muimaster.library",MUI_LIB_VERSION);

	if(IntuitionBase && DOSBase && UtilityBase && GfxBase && CxBase && IconBase && MUIMasterBase)
	{
		// If all libs are available, we open the MUI window
		MUIShowHide();
	}

	// Before leaving, we close all libraries
	cleanUP();

	if(wbmsg != NULL)
	{
		// If needed, we reply to the workbench message
		Forbid();
		ReplyMsg((struct Message *)wbmsg);
	}
}

__attribute__((used)) __attribute__((section(".text.unlikely"))) void _start(int argc, char **argv)
{
	main(argc,argv);
}