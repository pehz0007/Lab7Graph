#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

void DFS_I (Graph , int );

int main()
{
    Graph g;
    int i,j;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for DFS:\n");
    scanf("%d", &i);
    printGraphMatrix(g);
    DFS_I(g,i);

    return 0;
}

int getNextUnvisitedVertex(Graph *g, int* visited, int v) {
    for (int i = 0; i < g->V; i++) {
        if(i != v && g->matrix[v][i] == 1 && !visited[i])return i;
    }
    return -1;
}

void DFS_I (Graph g, int v)
{
    v = v-1;//Offset by 1
    Stack stack;
    stack.size = 0;
    stack.head = NULL;

    push(&stack, v);
    int *visited;
    visited = (int *) malloc(sizeof(int)*g.V);
    for(int i=0;i<g.V;i++) visited[i] = 0;
    visited[v] = 1;

    while(!isEmptyStack(stack)) {
        int w = peek(stack);
        int nextVertex = getNextUnvisitedVertex(&g, visited, w);

        if(nextVertex!=-1) {
            push(&stack, nextVertex);
            visited[nextVertex] = 1;
        }else {
            printf("%d ", w+1);
            pop(&stack);
        }


    }

    free(visited);

    // Stack s;
    // s.size = 0;
    // s.head = NULL;
    //
    // int i;
    // int w;
    //
    // int *visitV;
    // visitV = (int *) malloc(sizeof(int)*g.V);
    // for(i=0;i<g.V;i++) visitV[i] = 0;
    //
    // push(&s,v);
    // visitV[v-1] = 1;
    //
    // int unvisited; // no unvisited vertices flag
    // while(isEmptyStack(s)==0){
    //     w = peek(s);
    //
    //     unvisited = 0;
    //     for(i=0;i<g.V;i++)
    //     {
    //         if(g.matrix[w-1][i] == 1 && visitV[i]==0)
    //         {
    //             push(&s,i+1);
    //             visitV[i]=1;
    //             unvisited = 1;
    //             break;
    //         }
    //     }
    //
    //     if(unvisited==0){
    //        printf("%d ",w);
    //        pop(&s);
    //     }
    // }
    //
    // free(visitV);
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
