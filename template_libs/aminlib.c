#include <proto/exec.h>
#include <proto/utility.h>
#include <stdarg.h>

// We define here some functions of the amiga lib
// Again, all args are copied on the stack (due to gcc optimisations)
// This code is inspired by AROS code (https://github.com/aros-development-team/AROS)

#define ARG_CNT 32

ULONG CallHookA(struct Hook *hook,Object *obj,APTR msg)
{
    return(CallHookPkt(hook,obj,msg));
}

ULONG CallHook(struct Hook *hook,Object *obj,... )
{
    ULONG result = 0L;
	va_list param;
	APTR *msg;
	int i;

	if(obj != NULL)
	{
		if ((msg = AllocVec(ARG_CNT*sizeof(ULONG),MEMF_ANY)))
		{
			va_start(param,obj);
			
			for(int i=0;i<ARG_CNT;i++) {
				msg[i] = (APTR)va_arg(param,APTR);
			}

			va_end(param);

			result = CallHookA(hook,obj,(APTR)msg);
			FreeVec(msg);
		}
	}

	return(result);
}

ULONG CoerceMethodA(Class *cl,Object * obj,Msg msg)
{
    ULONG result = 0L;

    if(cl != NULL && obj != NULL)
		result = CallHookA(&cl->cl_Dispatcher,obj,msg);
}

ULONG CoerceMethod(Class *cl, Object *obj, ULONG method_id, ...)
{
	ULONG result = 0L;
	va_list param;
	ULONG *msg;
	int i;

	if(cl != NULL && obj != NULL)
	{
		if ((msg = AllocVec(ARG_CNT*sizeof(ULONG),MEMF_ANY)))
		{
			msg[0] = method_id;
			va_start(param,method_id);
			
			for(int i=1;i<ARG_CNT;i++) {
				msg[i] = (ULONG)va_arg(param,ULONG);
			}

			va_end(param);

			result = CoerceMethodA(cl,obj,(Msg)msg);
			FreeVec(msg);
		}
	}

	return(result);
}

ULONG DoMethodA(Object * obj,Msg msg)
{
	ULONG result = 0;

	if(obj != NULL)
	{
		Class *cl = OCLASS(obj);

		if(cl != NULL) {
			result = CallHookPkt(&cl->cl_Dispatcher,obj,msg);
		}
	}

	return(result);
}

ULONG DoMethod(Object *obj, ULONG method_id, ...)
{
	ULONG result = 0L;
	va_list param;
	ULONG *msg;
	int i;

	if(obj != NULL)
	{
		if ((msg = AllocVec(ARG_CNT*sizeof(ULONG),MEMF_ANY)))
		{
			msg[0] = method_id;
			va_start(param,method_id);
			
			for(int i=1;i<ARG_CNT;i++) {
				msg[i] = (ULONG)va_arg(param,ULONG);
			}

			va_end(param);

			result = DoMethodA(obj,(Msg)msg);
			FreeVec(msg);
		}
	}

	return(result);
}

ULONG DoSuperMethodA(Class * cl,Object * obj,Msg msg)
{
    ULONG result = 0L;

    if(cl != NULL && obj != NULL)
		result = CallHookA(&cl->cl_Super->cl_Dispatcher,obj,msg);

    return(result);
}

ULONG DoSuperMethod(Class *cl,Object *obj,ULONG method_id, ...)
{
    ULONG result = 0L;
	va_list param;
	ULONG *msg;
	int i;

    if(cl != NULL && obj != NULL)
    {
		if ((msg = AllocVec(ARG_CNT*sizeof(ULONG),MEMF_ANY)))
		{
			msg[0] = method_id;
			va_start(param,method_id);
			
			for(int i=1;i<ARG_CNT;i++) {
				msg[i] = (ULONG)va_arg(param,ULONG);
			}

			va_end(param);

			result = DoSuperMethodA(cl,obj,(Msg)msg);
			FreeVec(msg);
		}
    }

    return(result);
}


