#include <stdarg.h>
#include <utility/tagitem.h>

extern struct TagItem *CopyTagsToMem(Tag first,va_list param);
extern struct TagItem *FreeTagMem(struct TagItem *tagItem);
