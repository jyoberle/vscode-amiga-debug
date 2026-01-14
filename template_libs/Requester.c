#include "l_option.h"

#if OPTION_AMIGA_OS32
;/*
sc Requester.c LINK NOSTACKCHECK
quit
*/

//#define USE_BUILTIN_MATH
//#define USE_SYSBASE

#include <stdio.h>
#include <string.h>
#include <math.h>

#define	INTUI_V36_NAMES_ONLY

#include <exec/types.h>
#include <exec/memory.h>
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <proto/exec.h>
#define NO_INLINE_STDARG
#include <intuition/intuition.h>
#undef NO_INLINE_STDARG
#include <intuition/gadgetclass.h>
#include <intuition/intuitionbase.h>
#include <intuition/classusr.h>
#include <intuition/imageclass.h>
#include <intuition/gadgetclass.h>
#include <intuition/cghooks.h>
#include <intuition/icclass.h>
#include <intuition/classes.h>
#include <intuition/sghooks.h>
#include <graphics/gfxbase.h>
#include <graphics/text.h>
#include <graphics/gfxmacros.h>
#include <utility/tagitem.h>
#include <utility/hooks.h>

#include <clib/macros.h>
#include <proto/exec.h>
#include <proto/alib.h>

#define NO_INLINE_STDARG
#include <proto/intuition.h>
#undef NO_INLINE_STDARG
#include <proto/requester.h>
#include <proto/graphics.h>
#include <proto/dos.h>
#include <proto/gadtools.h>
#include <proto/utility.h>
#include <proto/button.h>
#include <proto/window.h>
#include <proto/layout.h>

#define ALL_REACTION_CLASSES
#define ALL_REACTION_MACROS
#include <reaction/reaction.h>
#include <reaction/reaction_macros.h>
// #include <reaction/reaction_author.h>

#include <classes/requester.h>
#include <classes/window.h>
#include <gadgets/button.h>
#include <gadgets/layout.h>

extern struct TagItem *CopyTagsToMem(Tag first,va_list param);
extern struct TagItem *FreeTagMem(struct TagItem *tagItem);

#define ID_BUTTON		1

ULONG OpenRequesterTags(Object *obj, struct Window *win, Tag, ...);

UBYTE *chooserlabels[] =
{
	"Label 1",
	"Label 2",
	"Label 3",
	"Label 4",
	NULL,
};

int main_requester( void )
{
	struct Window *window;
	Object *But_Object, *Req_Object;
	Object *Win_Object;
	UBYTE buffer[128] = "Edit me!";
	ULONG number = 0;

	Req_Object = RequesterObject,
		REQ_TitleText, "Simple requester.class example",
	EndMember,

	/* Create the window object. */
	Win_Object = WindowObject,
		WA_ScreenTitle, "ReAction",
		WA_Title, "ReAction Requester Example",
		WA_SizeGadget, TRUE,
		WA_Left, 40,
		WA_Top, 30,
		WA_DepthGadget, TRUE,
		WA_DragBar, TRUE,
		WA_CloseGadget, TRUE,
		WA_Activate, TRUE,
		WA_SmartRefresh, TRUE,
		WINDOW_ParentGroup, VLayoutObject,
			LAYOUT_SpaceOuter, TRUE,
			LAYOUT_DeferLayout, TRUE,
			StartMember, But_Object = ButtonObject,
				GA_RelVerify, TRUE,
				GA_ID, ID_BUTTON,
				GA_Text, "_Press Me!",
			ButtonEnd,
			CHILD_MinWidth, 100,
			CHILD_WeightedHeight, 0,
		EndMember,
	EndWindow;

	/*  Object creation sucessful?
	 */
	if( Win_Object )
	{
		/*  Open the window.
		 */
		if( window = (struct Window *) RA_OpenWindow(Win_Object) )
		{
			ULONG wait, signal, result, done = FALSE, retval;
			WORD Code;
				
			/* Obtain the window wait signal mask.
			 */
			GetAttr( WINDOW_SigMask, Win_Object, &signal );

			/* Input Event Loop
			 */
			while( !done )
			{
				wait = Wait(signal|SIGBREAKF_CTRL_C);
					
				if (wait & SIGBREAKF_CTRL_C) done = TRUE;
				else

				while ((result = RA_HandleInput(Win_Object,&Code)) != WMHI_LASTMSG)
				{
					switch (result & WMHI_CLASSMASK)
					{
						case WMHI_CLOSEWINDOW:
							done = TRUE;
							break;

						case WMHI_GADGETUP:
							switch(result & WMHI_GADGETMASK)
							{
								case ID_BUTTON:
									/* IMPORTANT: Note how the \33 sequence is not used for selecting pens! */
									retval = OpenRequesterTags(Req_Object, window, 
												REQ_Type, REQTYPE_INFO, 
												REQ_BodyText, "\33b\33c\33f[cgtimes.font/50]Information\nfor\nyou.",
												REQ_GadgetText, "_Ok", TAG_DONE);
									printf("returned: %ld\n", retval);
									retval = OpenRequesterTags(Req_Object, window, 
												REQ_Type, REQTYPE_INFO, 
												REQ_BodyText, "\33c\33iSome fancy text here just to show off.\33n\n\n\33bReAction\33n rules!\n\n5\33b\33f[helvetica.font/15]ReAction\33n3  is magic!",
												REQ_GadgetText, "_Ok|_Roll the bones!|_Whee!, get me out of here", TAG_DONE);
									printf("returned: %ld\n", retval);
									retval = OpenRequesterTags(Req_Object, window, 
												REQ_Type, REQTYPE_STRING, 
												REQS_Buffer, buffer,
												REQS_ShowDefault, FALSE,
												REQS_MaxChars, 127,
												REQ_GadgetText, "_Ok|_Cancel",
												REQ_BodyText, "Enter a string:", TAG_DONE);
									printf("returned: %ld, string: '%s'\n", retval, buffer);
									retval = OpenRequesterTags(Req_Object, window, 
												REQ_Type, REQTYPE_STRING, 
												REQS_Buffer, buffer,
												REQS_ShowDefault, TRUE,
												REQS_MaxChars, 127,
												REQS_ChooserArray, chooserlabels,
												REQS_ChooserActive, 2,
												REQ_GadgetText, "_Ok|_Patricia!|_Cancel",
												REQ_BodyText, "Edit the string:", TAG_DONE);
									GetAttr(REQS_ChooserActive, Req_Object, &number);
									printf("returned: %ld, string: '%s', active: %ld\n", retval, buffer, number);
									retval = OpenRequesterTags(Req_Object, window, 
												REQ_Type, REQTYPE_INTEGER, 
												REQI_Number, number,
												REQI_Arrows, TRUE,
												REQS_ChooserArray, NULL, /* reset the labels */
												REQ_GadgetText, "_Ok|_Cancel",
												REQ_BodyText, "Enter a number:", TAG_DONE);
									GetAttr(REQI_Number, Req_Object, &number);
									printf("returned: %ld, number: %ld\n", retval, number);
									retval = OpenRequesterTags(Req_Object, window, 
												REQ_Type, REQTYPE_INTEGER, 
												REQI_Number, number,
												REQI_Maximum, 1000,
												REQI_Minimum, -1000,
												REQI_Arrows, FALSE,
												REQ_GadgetText, "_Ok|_Cancel",
												REQ_BodyText, "Enter a number:", TAG_DONE);
									GetAttr(REQI_Number, Req_Object, &number);
									printf("returned: %ld, number: %ld\n", retval, number);
									break;
							}
							break;
					}
				}
			}
		}

		/* Disposing of the window object will
		 * also close the window if it is
		 * already opened and it will dispose of
		 * all objects attached to it.
		 */
		DisposeObject( Win_Object );
	}
	DisposeObject( Req_Object );
}

ULONG OpenRequesterTags(Object *obj, struct Window *win, ULONG Tag1, ...)
{
	struct orRequest msg[1];
	va_list param;
	struct TagItem *tagItem;
	ULONG ret;

  	va_start(param,Tag1);

	if((tagItem = CopyTagsToMem(Tag1,param))) 
	{
		msg->MethodID = RM_OPENREQ;
		msg->or_Window = win;	/* window OR screen is REQUIRED */
		msg->or_Screen = NULL;
		msg->or_Attrs = (struct TagItem *)tagItem;

		ret = DoMethodA(obj, (Msg)msg);
		FreeTagMem(tagItem);
	}

	va_end(param);
}
#endif