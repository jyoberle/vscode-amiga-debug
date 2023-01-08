#include <proto/utility.h>

extern ULONG CallHookA(struct Hook *hook,Object *obj,APTR msg);
extern ULONG CallHook(struct Hook *hook,Object *obj,... );
extern ULONG CoerceMethodA(Class *cl,Object * obj,Msg msg);
extern ULONG CoerceMethod(Class *cl, Object *obj, ULONG method_id, ...);
extern ULONG DoMethodA(Object * obj,Msg msg);
extern ULONG DoMethod(Object *obj, ULONG method_id, ...);
extern ULONG DoSuperMethodA(Class * cl,Object * obj,Msg msg);
extern ULONG DoSuperMethod(Class *cl,Object *obj,ULONG method_id, ...);
