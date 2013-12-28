#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_EDGES 30

typedef struct node *nodePointer;
struct node{
	int vertex;
	int duration;
	nodePointer link;
};

typedef struct{
	int count;
	int earliest;
	int latest;
	int pre;
	nodePointer first;
}hdnodes;
typedef struct{
	int edge;
	int early;
   	int late;
}Edge;	

hdnodes graph[MAX_VERTICES];
Edge g_edge[MAX_EDGES];

typedef enum {INPUT_MATRIX_1, INPUT_MATRIX_2}input_file;

int init_graph(input_file, int *);
void topSort(hdnodes [], int);
void calc_latest(hdnodes [], int);
nodePointer newNode();
void print_graph(int);
void print_result(int, int);

int main(void)
{
	int i, num_vertex = 0, num_edge = 0;

	/* Init graph */
	for(i=0; i<MAX_VERTICES; i++)
	{
		graph[i].count = 0;
		graph[i].first = NULL;	
		graph[i].earliest = 0;
		graph[i].latest = 100;
		graph[i].pre = 0;
	}
	for(i=0; i<MAX_EDGES; i++){
		g_edge[i].edge = 0;
		g_edge[i].early = 0;
		g_edge[i].late = 0;
	}

	printf("Please select input matrix: 1) or 2)\n");
	scanf("%d", &i);
	switch(i)
	{
		case 1:
			num_vertex = init_graph(INPUT_MATRIX_1, &num_edge);
			break;
		case 2:
			num_vertex = init_graph(INPUT_MATRIX_2, &num_edge);
			break;
	}
	printf("*** THE GRAPH for Adjancency Lists |V|=%d, |E|=%d ***\n", num_vertex, num_edge);
	print_graph(num_vertex);
	topSort(graph, num_vertex);
	calc_latest(graph, num_vertex);
	print_result(num_vertex, num_edge);

}

int init_graph(input_file in, int *num_edge)
{
	int i = 0, j = 0, num_vertex = 0;
	int k = 0;
	char c;
	nodePointer temp, node;
	FILE *fp;

	*num_edge = 0;
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
				g_edge[k++].edge = (int)(c-'0');
				graph[j].count++;
				temp = node;
				j++;
				(*num_edge)++;
			}
		}while(1);
		fclose(fp);
	}
	return num_vertex;
}

#if 1
void topSort(hdnodes graph[MAX_VERTICES], int n)
{
	int i, j, k, top, temp=-1;
	nodePointer ptr;

	top = -1;
	for(i = 0 ; i < n; i++)
		if(!graph[i].count){
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

			graph[j].pre = temp;
			temp = j;

			//printf("v%d, ",j);
			/* calculate < j, k > */
			for(ptr = graph[j].first; ptr; ptr = ptr->link){
				k = ptr->vertex;
				/* calculate the set of all vertex to 'k' */
				if(graph[k].earliest < graph[j].earliest + ptr->duration)
					graph[k].earliest = graph[j].earliest + ptr->duration;
				graph[k].count--;
				if(!graph[k].count){
					graph[k].count = top;
					top = k;
				}
			}
		}
}
#endif

void calc_latest(hdnodes graph[MAX_VERTICES], int n)
{
	int i, j;
	nodePointer temp;

	graph[n-1].latest = graph[n-1].earliest;
	
	/* calculate < i, k > */
	for(i = n-2; i > -1; i = graph[i].pre ){
		for(temp = graph[i].first; temp; temp = temp->link)
			if(graph[i].latest > graph[temp->vertex].latest - temp->duration)
				graph[i].latest = graph[temp->vertex].latest - temp->duration;
	}

}

void print_graph(int num)
{
	int i;
	nodePointer temp;

	printf("hdnode:\t\tnode\n");
	for(i = 0; i < num; i++){
		printf("[%d] %d", i, graph[i].count);
		printf("\t\t");
		if(graph[i].first != NULL){
			temp = graph[i].first;
			for(; temp; temp = temp->link){
				printf("(%d,%d) ", temp->vertex, temp->duration);
			}
		}
		printf("\n");
	}		
}

void print_result(int vertex, int edge)
{
	int i;

	printf("hdnode:V.# earliest/latest(previoes)\n");
	for(i = 0; i < vertex; i++){
		printf("V.%d %d/%d(%d) ", i, graph[i].earliest, graph[i].latest, graph[i].pre);
	printf("\t");
	}
	printf("\n==============\n");
	printf("edges:(a.# (weight))\n");
	for(i = 0; i < edge; i++){
		printf("a.%d (%d)", i+1, g_edge[i].edge);
		printf("\t");
	}
	printf("\n");
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

