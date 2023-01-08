#ifndef INLINE4_MUIMASTER_H
#define INLINE4_MUIMASTER_H

/*
** This file was auto generated by idltool 53.9.
**
** It provides compatibility to OS3 style library
** calls by substituting functions.
**
** Do not edit manually.
*/ 

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif

#ifndef INTUITION_CLASSES_H
#include <intuition/classes.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef LIBRARIES_MUI_H
#include <libraries/mui.h>
#endif
#include <interfaces/muimaster.h>

/* Inline macros for Interface "main" */
#define MUI_NewObjectA(cl, tags) IMUIMaster->MUI_NewObjectA((cl), (tags)) 
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
#define MUI_NewObject(...) IMUIMaster->MUI_NewObject(__VA_ARGS__) 
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
#define MUI_NewObject(vargs...) IMUIMaster->MUI_NewObject(## vargs) 
#endif
#define MUI_DisposeObject(obj) IMUIMaster->MUI_DisposeObject((obj)) 
#define MUI_RequestA(app, win, flags, title, gadgets, format, params) IMUIMaster->MUI_RequestA((app), (win), (flags), (title), (gadgets), (format), (params)) 
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
#define MUI_Request(app, win, flags, title, gadgets, ...) IMUIMaster->MUI_Request((app), (win), (flags), (title), (gadgets), __VA_ARGS__) 
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
#define MUI_Request(app, win, flags, title, gadgets, vargs...) IMUIMaster->MUI_Request(app, win, flags, title, gadgets, ## vargs) 
#endif
#define MUI_AllocAslRequest(type, tags) IMUIMaster->MUI_AllocAslRequest((type), (tags)) 
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
#define MUI_AllocAslRequestTags(...) IMUIMaster->MUI_AllocAslRequestTags(__VA_ARGS__) 
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
#define MUI_AllocAslRequestTags(vargs...) IMUIMaster->MUI_AllocAslRequestTags(## vargs) 
#endif
#define MUI_AslRequest(req, tags) IMUIMaster->MUI_AslRequest((req), (tags)) 
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
#define MUI_AslRequestTags(...) IMUIMaster->MUI_AslRequestTags(__VA_ARGS__) 
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
#define MUI_AslRequestTags(vargs...) IMUIMaster->MUI_AslRequestTags(## vargs) 
#endif
#define MUI_FreeAslRequest(req) IMUIMaster->MUI_FreeAslRequest((req)) 
#define MUI_Error() IMUIMaster->MUI_Error() 
#define MUI_SetError(errnum) IMUIMaster->MUI_SetError((errnum)) 
#define MUI_GetClass(name) IMUIMaster->MUI_GetClass((name)) 
#define MUI_FreeClass(cl) IMUIMaster->MUI_FreeClass((cl)) 
#define MUI_RequestIDCMP(obj, flags) IMUIMaster->MUI_RequestIDCMP((obj), (flags)) 
#define MUI_RejectIDCMP(obj, flags) IMUIMaster->MUI_RejectIDCMP((obj), (flags)) 
#define MUI_Redraw(obj, flags) IMUIMaster->MUI_Redraw((obj), (flags)) 
#define MUI_CreateCustomClass(base, supername, supermcc, datasize, dispatcher) IMUIMaster->MUI_CreateCustomClass((base), (supername), (supermcc), (datasize), (dispatcher)) 
#define MUI_DeleteCustomClass(mcc) IMUIMaster->MUI_DeleteCustomClass((mcc)) 
#define MUI_MakeObjectA(type, params) IMUIMaster->MUI_MakeObjectA((type), (params)) 
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
#define MUI_MakeObject(...) IMUIMaster->MUI_MakeObject(__VA_ARGS__) 
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
#define MUI_MakeObject(vargs...) IMUIMaster->MUI_MakeObject(## vargs) 
#endif
#define MUI_Layout(obj, l, t, w, h, flags) IMUIMaster->MUI_Layout((obj), (l), (t), (w), (h), (flags)) 
#define MUIP_private0() IMUIMaster->MUIP_private0() 
#define MUIP_private1() IMUIMaster->MUIP_private1() 
#define MUIP_private2() IMUIMaster->MUIP_private2() 
#define MUIP_private3() IMUIMaster->MUIP_private3() 
#define MUI_ObtainPen(mri, spec, flags) IMUIMaster->MUI_ObtainPen((mri), (spec), (flags)) 
#define MUI_ReleasePen(mri, pen) IMUIMaster->MUI_ReleasePen((mri), (pen)) 
#define MUI_AddClipping(mri, l, t, w, h) IMUIMaster->MUI_AddClipping((mri), (l), (t), (w), (h)) 
#define MUI_RemoveClipping(mri, h) IMUIMaster->MUI_RemoveClipping((mri), (h)) 
#define MUI_AddClipRegion(mri, region) IMUIMaster->MUI_AddClipRegion((mri), (region)) 
#define MUI_RemoveClipRegion(mri, region) IMUIMaster->MUI_RemoveClipRegion((mri), (region)) 
#define MUI_BeginRefresh(mri, flags) IMUIMaster->MUI_BeginRefresh((mri), (flags)) 
#define MUI_EndRefresh(mri, flags) IMUIMaster->MUI_EndRefresh((mri), (flags)) 
#define MUIP_private4() IMUIMaster->MUIP_private4() 
#define MUIP_private5() IMUIMaster->MUIP_private5() 
#define MUI_Show(obj) IMUIMaster->MUI_Show((obj)) 
#define MUI_Hide(obj) IMUIMaster->MUI_Hide((obj)) 
#define MUI_LayoutObj(obj, l, t, w, h, flags) IMUIMaster->MUI_LayoutObj((obj), (l), (t), (w), (h), (flags)) 
#define MUI_Offset(obj, x, y) IMUIMaster->MUI_Offset((obj), (x), (y)) 
#define MUIP_private6() IMUIMaster->MUIP_private6() 
#define MUIP_private7() IMUIMaster->MUIP_private7() 
#define MUIP_private8() IMUIMaster->MUIP_private8() 
#define MUIP_private9() IMUIMaster->MUIP_private9() 
#define MUIP_private10() IMUIMaster->MUIP_private10() 
#define MUIP_private11() IMUIMaster->MUIP_private11() 
#define MUIP_private12() IMUIMaster->MUIP_private12() 
#define MUIP_private13() IMUIMaster->MUIP_private13() 
#define MUIP_private14() IMUIMaster->MUIP_private14() 
#define MUIP_private15() IMUIMaster->MUIP_private15() 
#define MUIP_private16() IMUIMaster->MUIP_private16() 
#define MUIP_private17() IMUIMaster->MUIP_private17() 
#define MUIP_private18() IMUIMaster->MUIP_private18() 
#define MUIP_private19() IMUIMaster->MUIP_private19() 
#define MUIP_private20() IMUIMaster->MUIP_private20() 
#define MUIP_private21() IMUIMaster->MUIP_private21() 
#define MUIP_private22() IMUIMaster->MUIP_private22() 
#define MUIP_private23() IMUIMaster->MUIP_private23() 
#define MUIP_private24() IMUIMaster->MUIP_private24() 
#define MUIP_private25() IMUIMaster->MUIP_private25() 
#define MUIP_private26() IMUIMaster->MUIP_private26() 
#define MUIP_private27() IMUIMaster->MUIP_private27() 
#define MUIP_private28() IMUIMaster->MUIP_private28() 
#define MUIP_private29() IMUIMaster->MUIP_private29() 
#define MUIP_private30() IMUIMaster->MUIP_private30() 
#define MUIP_private31() IMUIMaster->MUIP_private31() 
#define MUIP_private32() IMUIMaster->MUIP_private32() 
#define MUIP_private33() IMUIMaster->MUIP_private33() 
#define MUIP_private34() IMUIMaster->MUIP_private34() 
#define MUIP_private35() IMUIMaster->MUIP_private35() 
#define MUIP_private36() IMUIMaster->MUIP_private36() 
#define MUIP_private37() IMUIMaster->MUIP_private37() 
#define MUIP_private38() IMUIMaster->MUIP_private38() 
#define MUIP_private39() IMUIMaster->MUIP_private39() 
#define MUIP_private40() IMUIMaster->MUIP_private40() 
#define MUIP_private41() IMUIMaster->MUIP_private41() 
#define MUIP_private42() IMUIMaster->MUIP_private42() 
#define MUIP_private43() IMUIMaster->MUIP_private43() 
#define MUIP_private44() IMUIMaster->MUIP_private44() 
#define MUIP_private45() IMUIMaster->MUIP_private45() 
#define MUIP_private46() IMUIMaster->MUIP_private46() 
#define MUIP_private47() IMUIMaster->MUIP_private47() 
#define MUIP_private48() IMUIMaster->MUIP_private48() 
#define MUIP_private49() IMUIMaster->MUIP_private49() 

#endif /* INLINE4_MUIMASTER_H */
