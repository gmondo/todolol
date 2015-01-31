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
#define MAX_PATH	MAX_DESCR * 5
#define DATA_FILE	"todolol.txt"

typedef struct elem {
	char	descr[MAX_DESCR];
	struct	elem *sub;
	struct	elem *next;
} t_elem;

void interact_load(t_elem**, char*, FILE*);
void save(t_elem*, FILE*);

int main() {
	t_elem *head = NULL;
	char *path = malloc(MAX_PATH);
	FILE *fp;
	strcpy(path, "/");

	fp = fopen(DATA_FILE, "r");
	if (NULL != fp) {
		interact_load(&head, path, fp);
		fclose(fp);
	}
	
	interact_load(&head, path, stdin);

	fp = fopen(DATA_FILE, "w");	
	save(head, fp);
	fclose(fp);
} /* main */

void interact_load(t_elem **head, char *path, FILE *fin) {
	char	ans[MAX_ANS];
	int	count, num;
	t_elem	*cur, *prev, *new;

	while(1) {
		cur = *head;
		count = 1;
		if (stdin == fin) {
			printf("%s\n", path);
			while ( NULL != cur ) {
				printf("%d) %s\n", count++, cur->descr);
				cur = cur->next;
			}
			printf(	"Commands: a(dd)#, r(emove)#, d(own)#, g(o)#, b(ack or quit)\n"
				"(e.g. type c3 to go to 3rd list). Command: ");
		}
		if (1 > fscanf(fin, "%s", ans) || 'b'==ans[0]) {
			return;
		}

		/* set pointers */
		num = atoi(ans+1);
		cur = *head;
		prev = *head;
		for (count = 1; count < num && NULL != cur; count++) {
			prev = cur;
			cur = cur->next;
		}
		if ('a'!=ans[0] && NULL==cur) {
			continue;
		}
	
		switch (ans[0]) {
			case 'a':
				if (stdin == fin) {
					printf("Description: ");
				}
				fscanf(fin, "%s", ans);
				new = malloc(sizeof(t_elem));
				strcpy(new->descr, ans);
				new->sub = NULL;
				new->next = cur;
				if (cur == prev) {
					*head = new;
				} else {
					prev->next = new;
				}
				break;
			case 'r':
				/*
				printf("Element to delete: %s\n", cur->descr);
				*/
				if (*head==cur) {
					*head = (*head)->next;
				} else {
					prev->next = cur->next;	
				}
				free(cur);
				break;
			case 'd':
				if (NULL == cur->next) {
					break;
				}
				/*
				printf("Get down: %s\n", cur->descr);
				*/
				if (cur == prev) {
					*head = cur->next;
					cur->next = (*head)->next;
					(*head)->next = cur;
					break;
				}
				prev->next = cur->next;
				cur->next = prev->next->next;
				prev->next->next = cur;
				break;
			case 'g':
				if (strlen(path) + strlen(cur->descr) + 1 < MAX_PATH) {
					strcat(path, cur->descr);
					strcat(path, "/");
					interact_load(&cur->sub, path, fin);
					path[strlen(path)-strlen(cur->descr)-1]=0;
				}
				break;
		}	/* switch */
	}	/* while */
} /* interact_load */

void save(t_elem* head, FILE *fout) {
	int count = 1;
	t_elem 	*cur = head;
	
	while (NULL != cur) {
		fprintf(fout, "a%d\n%s\n", count, cur->descr);
		if (NULL != cur->sub) {
			fprintf(fout, "g%d\n", count);
			save(cur->sub, fout);
			fprintf(fout, "b\n");
		}
		count++;
		cur = cur->next;
	}
} /* save */
