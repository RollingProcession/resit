#include <stdio.h>

typedef struct LNode
{
    char name[10];
    char pass[10];
	char pass2[10];
    struct LNode *next;
} LNode,*pNode;
