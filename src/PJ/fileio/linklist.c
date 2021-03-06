/* linklist.c doubly linked list utilities */

#include "linklist.h"
#include "memory.h"

#define SAFETY  

/***********************************************************/
/* DOUBLY linked list (dl) calls */
/***********************************************************/
#ifdef SAFETY  
void safe_rem_node(register Dlnode *node)
{
	if(node->next == NULL)
		return;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->next = NULL;
}
#endif /* SAFETY */
/***********************************************************/
/* returns length of doubly linked list */

LONG listlen(Dlheader *list)
{
register Dlnode *node;
register Dlnode *next;
register LONG len;

	for(node = list->head, len = 0;
		NULL != (next = node->next);
		node = next)
	{
		++len;
	}
	return(len);
}
/***********************************************************/
/* returns header node is attached to 
 * (if SAFETY returns NULL if not attached) */

Dlheader *find_header(register Dlnode *node)
{
#ifdef SAFETY
	if(node->next == NULL)
		return(NULL);
#endif /* SAFETY */

	while(node->prev != NULL)
		node = node->prev;
	return((Dlheader *)node);
}
/****************************************************************/
Boolean isin_list(register Dlnode *testnode,Dlheader *list)

/* returns 1 if node found in list 0 if not */
{
register Dlnode *node;

	node = list->head;
	while(node->next != NULL)
	{
		if(testnode == node)
			return(1);
		node = node->next;
	}
	return(0);
}
/****************************************************************/
/* inserts a node in a list given compare function and the list
 * only works if list is in sorted order using this compare function */

void insert_compare(register Dlnode *node,
					Dlheader *list,
					FUNC compare)
/* FUNC a function that is called given *node A and *node B
 * compare(Dlnode *nodea Dlnode *nodeb) returns 0 if
 * A == B, < 0 if A < B, > 0 if A > B */
{
register Dlnode *lnode; /* current list node */
register Dlnode *nextnode;

	for(lnode = list->tails_prev;
	    NULL != (nextnode = lnode->prev);
		lnode = nextnode)
	{
		if((*compare)(node,lnode) > 0)
			break;
	}
	insert_after(node,lnode);
}
/*************************************************************/
/* insert sorts a list given compare function and the list
 * list will be in ascending order based on compare() */

void isort_list(Dlheader *list, FUNC compare)

/* a function that is called given *node A and *node B
 * compare(Dlnode *nodea Dlnode *nodeb) returns 0 if
 * A == B, < 0 if A < B, > 0 if A > B */
{
Dlheader tlist; /* tempory list */
Dlnode *node;

	init_list(&tlist);
	list_tohead(list,&tlist);

	while(NULL != (node = get_head(&tlist)))
		insert_compare(node,list,compare);
}

/* some sort routines.  Why here??? Why not??? */
void sort_indarray(void **array, LONG count, FUNC cmp, void *cmpdat)

/* a little shell on an array of indirect pointers to things.
 * takes a function that is like strcmp() to compare things pointed to */
{
register void **pt1, **pt2;
register void *swap;
register LONG swaps;
register LONG space, ct;

	if (count < 2)  /*very short arrays are already sorted*/
		return;

	space = count/2;
	--count; /* since look at two elements at once...*/
	for (;;)
	{
		swaps = 1;
		while (swaps)
		{
			pt1 = array;
			pt2 = array + space;
			ct = count - space + 1;
			swaps = 0;
			while (--ct >= 0)
			{
				if ((*cmp)(*pt1, *pt2, cmpdat) < 0)
				{
					swaps = 1;
					swap = *pt1;
					*pt1 = *pt2;
					*pt2 = swap;
				}
				pt1++;
				pt2++;
			}
		}
		if ( (space /= 2) == 0)
			break;
	}
}

