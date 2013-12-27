#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_BUF 100

typedef struct node *nodePointer;
struct node{
	int vertex;
	int duration;
	nodePointer link;
};
typedef struct{
	int count;
	nodePointer first;
}hdnodes;
hdnodes graph[MAX_VERTICES];

typedef enum {INPUT_MATRIX_1, INPUT_MATRIX_2}input_file;

int init_graph(input_file);
void topSort(hdnodes, int);
nodePointer newNode();
void print_graph(int);

int main(void)
{
	int i, num_vertex = 0;

	/* Init graph */
	for(i=0; i<MAX_VERTICES; i++)
	{
		graph[i].count = 0;
		graph[i].first = NULL;	
	}

	printf("Please select input matrix: 1) or 2)\n");
	scanf("%d", &i);
	switch(i)
	{
		case 1:
			num_vertex = init_graph(INPUT_MATRIX_1);
			break;
		case 2:
			num_vertex = init_graph(INPUT_MATRIX_2);
			break;
	}
	//topSort(graph[], 10);
	print_graph(num_vertex);
}

int init_graph(input_file in)
{
	int i = 0, j = 0, num_vertex = 0;
	char c;
	nodePointer temp, node;
	FILE *fp;

	temp = newNode();

	switch(in)
	{
		case INPUT_MATRIX_1:
			fp = fopen("input_matrix", "r");
			break;
		case INPUT_MATRIX_2:
			fp = fopen("input_matrix_2", "r");
			break;
	}

	if(fp == NULL)	printf("open file error\n");
	else{
		do{
			c = fgetc(fp);
			//printf("%c", c);
			if(c == EOF) 
				break;
			else if(c == ','){
				continue;
			}
			else if(c == '\n'){ 
				i++;
				num_vertex = j;
				j = 0;
			}
			else if(c == '0')
				j++;
			else if(c != '0'){
				node = newNode();
				if(graph[i].first == NULL)
					graph[i].first = node;
				else
					temp->link = node;
				node->vertex = j;
				node->duration = (int)(c-'0');
				node->link = NULL;
				graph[j].count++;
				temp = node;
				j++;
			}
		}while(1);
		fclose(fp);
	}
	return num_vertex;
}

#if 0
void topSort(hdnodes graph[], int n)
{
	int i, j, k, top;
	nodePointer ptr;

	top = -1;
	for(i = 0 ; i < n; i++)
		if(!graph.count){
			graph[i].count = top;
			top = i;
		}
	for(i = 0; i < n; i++)
		if(top == -1){
			fprintf(stderr, "\nNetwork has a cycle. Sort terminated.\n");
			exit(EXIT_FAILURE);
		}
		else{
			j = top;
			top = graph[top].count;
			printf("v%d, ",j);
			for(ptr = graph[j].link; ptr; ptr = ptr->link){
				k = ptr->vertex;
				graph[k].count--;
				if(!graph[k].count){
					graph[k].count = top;
					top = k;
				}
			}
		}
}
#endif

void print_graph(int num)
{
	int i;
	nodePointer temp;

	printf("hdnode:\tnode\n");
	for(i = 0; i < num; i++){
		printf("[%d] %d ", i, graph[i].count);
		printf("\t");
		if(graph[i].first != NULL){
			temp = graph[i].first;
			for(; temp; temp = temp->link){
				printf("(%d,%d) ", temp->vertex, temp->duration);
			}
		}
		printf("\n");
	}		
}

nodePointer newNode()
{
	nodePointer temp;
	if(!(temp = malloc(sizeof(*temp)))){
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	return temp;
}

