#include <stdarg.h>
#include <proto/exec.h>
#include <utility/tagitem.h>

// Copies tags from stack to memory
struct TagItem *CopyTagsToMem(Tag first,va_list param)
{
	int i,cnt = 1; // for the final tag
	va_list param2;
	Tag tag = first;
	struct TagItem *tagItem;

	// Count number of tags
	va_copy(param2,param);

	while(tag != TAG_DONE)
	{
		va_arg(param2,ULONG); // ti_Data
		tag = (Tag)va_arg(param2,Tag); // ti_Tag
		cnt++;
	}

	va_end(param2);

	// Copy all tags to memory
	if ((tagItem = (struct TagItem *)AllocVec(cnt*sizeof(struct TagItem),MEMF_ANY)))
	{
		tag = first;

		for(i=0;i < cnt;i++)
		{
			tagItem[i].ti_Tag = tag;

			if(tag == TAG_DONE)
				break;

			tagItem[i].ti_Data = (ULONG)va_arg(param,ULONG); // ti_Data
			tag = (Tag)va_arg(param,Tag); // ti_Tag	
		}
	}

	return(tagItem);
}

// Frees the memory allocated to store tags
struct TagItem *FreeTagMem(struct TagItem *tagItem)
{
	FreeVec((APTR)tagItem);
}