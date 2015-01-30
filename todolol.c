/*
**	Todo List of List is a simple portable C program to manage list of lists.
**      As an example you can use it to keep track of your activities:
**	activities done in different places can be subdivided in tasks with a next step to do and so on.
**	From time to time you can launch again this todolol to update things done.
**
**	Author:	Giovanni Mondo	(giovanni.mondo@yahoo.it)
**	Date:	2015/01/28
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DAT_NAME	"todolol.dat"
#define MAX_DESCR	80
#define MAX_ANS		MAX_DESCR + 2

typedef struct elem {
	char	descr[MAX_DESCR];
	struct	elem *sub;
	struct	elem *next;
} t_elem;

void recurse(t_elem*);

int main() {
	t_elem *head = NULL;

	recurse(head);
}

void recurse(t_elem *head) {
	char	ans[MAX_ANS];
	int	count;	
	t_elem	*cur;

	do {
		cur = head;
		count = 1;
		while ( NULL != cur ) {
			printf("%d) %s\n", count++, cur->descr);
			cur = cur->next;
		}
		printf(	"Commands: a(dd) name, r(emove) #, g(o) #, (u)p #, (d)own #, b(ack), (q)uit\n"
			"(e.g. type c3 to go to 3rd list). Command: ");
		scanf("%s", ans);
		switch (ans[0]) {
			case 'a': 
				cur = malloc(sizeof(t_elem));
				strcpy(cur->descr, ans+1);
				cur->sub = NULL;
				cur->next = head;
				head = cur;
				break;
		}
	} while ( 'q' != ans[0] );
} /* main */
