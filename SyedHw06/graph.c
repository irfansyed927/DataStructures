// Homework by Irfan Syed 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} bool;

#define MAXV 100

typedef struct edgenode {
    int y;
    int weight;
    struct edgenode *next;
} edgenodeT;

typedef struct {
    edgenodeT *edges[MAXV+1];
    int degree[MAXV+1];
    bool visited[MAXV+1];
    int nvertices;
    int nedges;  // number of directed edges....
    bool directed;
} graphT;

typedef int *queueElementT;
typedef struct queueCDT *queueADT;
typedef char *string;

struct queueCDT {
    queueElementT elements[6];
    int head;
    int tail;
};

void initialize_graph(graphT *g, bool directed);
void read_graph(graphT *g, char *filename);
void insert_edge(graphT *g, int x, int y, int w);
void delete_edge(graphT *g, int x, int y);
void print_graph(graphT *g, char *name);
void print_degree(graphT *g, char *name);
void print_complement(graphT *g, char *name);
void eliminate_links(graphT *g, int minW, int maxW);
void different_links(graphT *g, graphT *g2);
void common_links(graphT *g, graphT *g2);
void DFS_print(graphT *g, int v);
void BFS_print(graphT *g, int start);
bool isconnected(graphT *g);
void connected(graphT *g, int v);
int numofconncomp(graphT *g);
void free_graph(graphT *g);
graphT *copy_graph(graphT *g);
string GetLine(void);
string ReadLine(FILE *infile);
static void HelpCommand(void);
queueADT NewQueue(void);
void Enqueue(queueADT queue, queueElementT element);
queueElementT Dequeue(queueADT queue);
bool QueueIsEmpty(queueADT queue);
bool QueueIsFull(queueADT queue);
// put prototypes for other functions here....

void Reset_Visited(graphT *g) {
    int i;
    for (i = 1; i <= g->nvertices; i++) {
        if (g->visited[i] == TRUE) {
            g->visited[i] = FALSE;
        }
    }
}

//execution starts here
int main(int argc, char *argv[]) {
    graphT   *myg1=NULL, *myg2=NULL;
    if(argc < 2){
        fprintf(stderr, "Usage: %s graph_filename", argv[0]);
        exit(-1);
    }
    myg1 = (graphT *) malloc(sizeof(graphT));
    if (myg1 == NULL) {
        fprintf(stderr, "Cannot allocate memory for the graph");
        exit(-1);
    }
    initialize_graph(myg1, FALSE);
    read_graph(myg1, argv[1]);
    print_graph(myg1, "myg1");
    // first implement copy_graph function and call it here myg2 = copy_graph(myg1);
    print_graph(myg2, "myg2");
    // NOW in a loop get commands and
    // call related functions to perform them...
    while(TRUE) {
        printf("*");
        char *token, *graph, *x, *y, *w, *minW, *maxW, *graph2;
        string line = GetLine();
        token = strtok(line, " ");
        graph = strtok(NULL, " ");
        //command insert edges at x and y with weight of w
        if(!strcmp(token, "insert")) {
            
            x = strtok(NULL, " ");
            if(x == NULL) break;
            y = strtok(NULL, " ");
            if(y == NULL) break;
            w = strtok(NULL, " ");
            if(w == NULL) break;
            
            if(!strcmp(graph, "myg1")) insert_edge(myg1, atoi(x), atoi(y), atoi(w));
            else if(!strcmp(graph, "myg2")) insert_edge(myg2, atoi(x), atoi(y), atoi(w));
            //command delete edges at x and y
        } else if(!strcmp(token, "delete")) {
            
            x = strtok(NULL, " ");
            if(x == NULL) break;
            y = strtok(NULL, " ");
            if(y == NULL) break;
            
            if(!strcmp(graph, "myg1")) {
                delete_edge(myg1, atoi(x), atoi(y));
                if(myg1->directed == FALSE)
                    delete_edge(myg1, atoi(y), atoi(x));
            } else if(!strcmp(graph, "myg2")) {
                delete_edge(myg2, atoi(x), atoi(y));
                if(myg2->directed == FALSE)
                    delete_edge(myg2, atoi(y), atoi(x));
            }
            //command printgraph displays each node and their edges and weights
        } else if(!strcmp(token, "printgraph")) {
            
            if(!strcmp(graph, "myg1")) print_graph(myg1, "myg1");
            else if(!strcmp(graph, "myg2")) print_graph(myg2, "myg2");
            //command printdegree displays degree of each node
        } else if(!strcmp(token, "printdegree")) {
            if(!strcmp(graph, "myg1")) print_degree(myg1, "myg1");
            else if(!strcmp(graph, "myg2")) print_degree(myg2, "myg2");
            //commmand printcomplement displays complement of graph
        } else if(!strcmp(token, "printcomplement")) {
            
            if(!strcmp(graph, "myg1")) print_complement(myg1, "myg1");
            else if(!strcmp(graph, "myg2")) print_complement(myg2, "myg2");
            //command eliminatelinks deletes links less than minW and greater than maxW
        } else if(!strcmp(token, "eliminatelinks")) {
            minW = strtok(NULL, " ");
            if(minW == NULL) break;
            maxW = strtok(NULL, " ");
            if(maxW == NULL) break;
            
            if(!strcmp(graph, "myg1")) eliminate_links(myg1, atoi(minW), atoi(maxW));
            else if(!strcmp(graph, "myg2")) eliminate_links(myg2, atoi(minW), atoi(maxW));
            //command differentlinks displays links in graph 1 but not in graph 2
        } else if(!strcmp(token, "differentlinks")) {
            graph2 = strtok(NULL, " ");
            if(graph2 == NULL) break;
            
            if(!strcmp(graph, "myg1") && !strcmp(graph2, "myg2")) different_links(myg1, myg2);
            else if(!strcmp(graph, "myg2") && !strcmp(graph2, "myg1")) different_links(myg2, myg1);
            //command common links displays links in both graphs
        } else if(!strcmp(token, "commonlinks")) {
            graph2 = strtok(NULL, " ");
            if(graph2 == NULL) break;
            
            if(!strcmp(graph, "myg1") && !strcmp(graph2, "myg2")) common_links(myg1, myg2);
            else if(!strcmp(graph, "myg2") && !strcmp(graph2, "myg1")) common_links(myg2, myg1);
            //command dfs_print prints depth first search of graph
        } else if(!strcmp(token, "dfs_print")) {
            
            x = strtok(NULL, " ");
            if(x == NULL) break;
            
            if(!strcmp(graph, "myg1")) {
                DFS_print(myg1, atoi(x));
                Reset_Visited(myg1);
            } else if(!strcmp(graph, "myg2")) {
                DFS_print(myg2, atoi(x));
                Reset_Visited(myg2);
            }
            //command bfs_print prints breadth first search of graph
        } else if(!strcmp(token, "bfs_print")) {
            
            x = strtok(NULL, " ");
            if(x == NULL) break;
            
            if(!strcmp(graph, "myg1")) {
                BFS_print(myg1, atoi(x));
                Reset_Visited(myg1);
            } else if(!strcmp(graph, "myg2")) {
                BFS_print(myg2, atoi(x));
                Reset_Visited(myg2);
            }
            //command isconnected prints if graph is connected
        } else if(!strcmp(token, "isconnected")) {
            
            if(!strcmp(graph, "myg1")) {
                if(myg1->directed == TRUE) {
                    printf("Purchase the next version of this program.\n");
                } else if(isconnected(myg1)) {
                    printf("myg1 is connected\n");
                    Reset_Visited(myg1);
                } else {
                    printf("myg1 is not connected\n");
                    Reset_Visited(myg1);
                }
            } else if(!strcmp(graph, "myg2")) {
                if(myg2->directed == TRUE) {
                    printf("Purchase the next version of the program.\n");
                } else if(isconnected(myg2)) {
                    printf("myg2 is connected\n");
                    Reset_Visited(myg2);
                } else {
                    printf("myg2 is not connected\n");
                    Reset_Visited(myg2);
                }
            }
            //command numofconncomp prints number of connected components
        } else if(!strcmp(token, "numofconncomp")) {
            
            if(!strcmp(graph, "myg1")) {
                if(myg1->directed == TRUE) {
                    printf("Purchase the next version of the program.\n");
                } else { printf("Number of connected components is %d\n", numofconncomp(myg1)); Reset_Visited(myg1); }
            } else if(!strcmp(graph, "myg2")) {
                if(myg2->directed == TRUE) {
                    printf("Purchase the next version of the program.\n");
                } else { printf("Number of connected components is %d\n", numofconncomp(myg2)); Reset_Visited(myg2); }
            }
            //command help prints command menu
        } else if(!strcmp(token, "help")) {
            
            HelpCommand();
            //command quit ends program
        } else if(!strcmp(token, "quit")) {
            free_graph(myg1);
            free_graph(myg2);
            exit(0);
        } else {
            printf("Not valid\n");
        }
    }
}

void initialize_graph(graphT *g, bool directed) {
    int i;
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;
    for (i = 1; i <= MAXV; i++)
        g->edges[i] = NULL;
    for (i=1; i<=MAXV; i++)
        g->degree[i] = 0;
}

void read_graph(graphT *g, char *filename) {
    int i;
    int n, m, dir;
    int x, y, w;
    FILE *fp;
    if ((fp = fopen(filename,"r")) == NULL) {
        fprintf(stderr, "Cannot open the graph file");
        exit(-1);
    }
    fscanf(fp,"%d %d %d", &n, &m, &dir);
    g->nvertices = n;
    g->nedges  = 0; // insert function will increase it;
    g->directed  = dir;
    for (i = 1; i <= m; i++) {
        fscanf(fp,"%d %d %d", &x, &y, &w);
        insert_edge(g, x, y, w);
        if(dir == FALSE)
            insert_edge(g, y, x, w);
    }
    fclose(fp);
}

void insert_edge(graphT *g, int x, int y, int w) {
    edgenodeT *pe, *temp;
    pe = malloc(sizeof(edgenodeT)); // check if NULL pe->weight = w;
    pe->y = y;
    // YOU MUST MODIFY THIS FUNCTION SO IT WILL KEEP LINK LIST SORTED // W.R.T. NEIGHBOR IDs.
    pe->weight = w;
    
    temp = g->edges[x];
    
    if (x == y || x > g->nvertices || y > g->nvertices || x < 1 || y < 1) {
        printf("Invalid. Please try again.\n");
        return;
    }
    if (temp == NULL || temp->y > y) {
        pe->next = g->edges[x];
        g->edges[x] = pe;
    } else {
        while (temp->next != NULL && temp->next->y < y)
            temp = temp->next;
        if (temp->next != NULL && temp->next->y == y)
            return;
        pe->next = temp->next;
        temp->next = pe;
    }
    g->degree[x]++;
    g->nedges++;
}

void print_graph(graphT *g, char *name) {
    edgenodeT *pe;
    int i;
    if(!g)
        return;
    printf("Graph Name: %s\n", name);
    for (i = 1; i <= g->nvertices; i++) {
        printf("Node %d: ", i);
        pe = g->edges[i];
        while(pe){
            printf(" %d(w=%d),", pe->y, pe->weight);
            pe = pe->next;
        }
        printf("\n");
    }
}

void free_graph(graphT *g) {
    edgenodeT *pe, *olde;
    int i;
    for (i = 1; i <= g->nvertices; i++) {
        pe = g->edges[i];
        while(pe){
            olde = pe;
            pe = pe->next;
            free(olde);
        } }
    free(g);
}

graphT *copy_graph(graphT *g) {
    graphT *newg;
    // I simply return the same graph as a copy
    // but you really need to dynamically create
    // another copy of the given graph
    edgenodeT *pe;
    int i;
    newg = g; //maybe not needed
    newg = malloc(sizeof(graphT));
    if (newg == NULL)
        return NULL;
    
    newg->nvertices = g->nvertices;
    newg->nedges = g->nedges;
    newg->directed = g->directed;
    for (i = 1; i <= newg->nvertices; i++) {
        pe = g->edges[i];
        while (pe) {
            insert_edge(newg, i, pe->y, pe->weight);
            if (newg->directed == FALSE)
                insert_edge(newg, pe->y, i, pe->weight);
            pe = pe->next;
        }
    }
    return newg;
}

void delete_edge(graphT *g, int x, int y) {
    edgenodeT *pe, *prev;
    prev = NULL;
    
    if (x == y || x > g->nvertices || y > g->nvertices || x < 1 || y < 1) {
        printf("Invalid. Please try again.\n");
        return;
    }
    for (pe = g->edges[x]; pe != NULL; pe = pe->next) {
        if (pe->y == y) {
            if (prev == NULL)
                g->edges[x] = pe->next;
            else
                prev->next = pe->next;
            free(pe);
        }
        prev = pe;
    }
    g->degree[x]--;
    g->nedges--;
}

void print_degree(graphT *g, char *name) {
    edgenodeT *pe;
    int i;
    if (!g)
        return;
    printf("Graph Name: %s\n", name);
    for (i = 1; i <= g->nvertices; i++) {
        printf("Node %d degree: ", i);
        pe = g->edges[i];
        printf(" %d", g->degree[i]);
        printf("\n");
    }
    
    if(g->directed == TRUE) {
        printf("Graph %s is directed\n", name);
    }
}

void print_complement(graphT *g, char *name) {
    edgenodeT *pe;
    int i, x, z;
    int s[g->nvertices];
    printf("Complement Graph Of %s\n", name);
    for (i = 1; i <= g->nvertices; i++) {
        printf("Node %d Complement: ", i);
        pe = g->edges[i];
        z = x = 1;
        
        while (pe != NULL) {
            s[x] = pe->y;
            x++;
            pe= pe->next;
        }
        x = 1;
        pe = g->edges[i];
        while (x <= g->nvertices) {
            if (x == i) {
                x++;
                continue;
            }
            if (x != s[z]) {
                printf(" %d(w=%d),", x, 5);
            }
            x++;
            if(s[z] < x) z++;
        }
        for (z = 0; z <= g->nvertices; z++) {
            s[z] = 0;
        }
        printf("\n");
    }
}

void eliminate_links(graphT *g, int minW, int maxW) {
    edgenodeT *pe;
    int i;
    if (minW > maxW)
        return;
    for (i = 1; i <= g->nvertices; i++) {
        pe = g->edges[i];
        while (pe != NULL) {
            if (pe->weight < minW || pe->weight > maxW) {
                delete_edge(g, i, pe->y);
            }
            pe = pe->next;
        }
    }
}

void different_links(graphT *g, graphT *g2) {
    edgenodeT *pe, *pe2;
    int i;
    for (i = 1; i <= g->nvertices; i++) {
        pe = g->edges[i];
        pe2 = g2->edges[i];
        printf("Node %d different links:", i);
        while (pe != NULL || pe2 != NULL) {
            if (pe == NULL) {
                printf(" %d,", pe2->y);
                pe2 = pe2->next;
            } else if (pe2 == NULL) {
                printf(" %d,", pe->y);
                pe = pe->next;
            } else if (pe->y == pe2->y) {
                pe = pe->next;
                pe2 = pe2->next;
            } else if (pe->y < pe2->y) {
                printf(" %d,", pe->y);
                pe = pe->next;
            } else if (pe2->y < pe->y) {
                printf(" %d,", pe2->y);
                pe2 = pe2->next;
            }
        }
        printf("\n");
    }
}

void common_links(graphT *g, graphT *g2) {
    edgenodeT *pe, *pe2;
    int i;
    for (i = 1; i <= g->nvertices; i++) {
        pe = g->edges[i];
        pe2 = g2->edges[i];
        printf("Node %d common links:", i);
        while (pe != NULL && pe2 != NULL) {
            if (pe->y == pe2->y) {
                printf(" %d,", pe->y);
                pe = pe->next;
                pe2 = pe2->next;
            } else if (pe->y < pe2->y) {
                pe = pe->next;
            } else if (pe2->y < pe->y) {
                pe2 = pe2->next;
            }
        }
        printf("\n");
    }
}

void DFS_print(graphT *g, int v) {
    edgenodeT *pe;
    if (g == NULL)
        return;
    g->visited[v] = TRUE;
    printf("%d is visited\n", v);
    pe = g->edges[v];
    while (pe != NULL) {
        if (g->visited[pe->y] == FALSE) {
            DFS_print(g, pe->y);
        }
        pe = pe->next;
    }
}

void BFS_print(graphT *g, int start) {
    queueADT q;
    edgenodeT *pe;
    int v;
    if (g==NULL)
        return;
    q = NewQueue();
    Enqueue(q, &start);
    g->visited[start] = TRUE;
    printf("%d is visited\n", start);
    while (QueueIsEmpty(q) == FALSE) {
        v = *Dequeue(q);
        pe = g->edges[v];
        while (pe != NULL) {
            if (g->visited[pe->y] == FALSE) {
                Enqueue(q, &pe->y);
                g->visited[pe->y] = TRUE;
                printf("%d is visited\n", pe->y);
            }
            pe = pe->next;
        }
    }
    free(q);
}

void connected(graphT *g, int v) {
    edgenodeT *pe;
    if (g == NULL)
        return;
    g->visited[v] = TRUE;
    pe = g->edges[v];
    while (pe != NULL) {
        if (g->visited[pe->y] == FALSE) {
            connected(g, pe->y);
        }
        pe = pe->next;
    }
}

bool isconnected(graphT *g) {
    connected(g, 1);
    
    int i;
    for (i = 1; i <= g->nvertices; i++) {
        if (g->visited[i] == FALSE) {
            return FALSE;
        }
    }
    return TRUE;
}

int numofconncomp(graphT *g) {
    int i, count = 0;
    for (i = 1; i <= g->nvertices; i++) {
        if(g->visited[i] == FALSE) {
            connected(g, i);
            count++;
        }
    }
    return count;
}

string GetLine(void) {
    return (ReadLine(stdin));
}

string ReadLine(FILE *infile) {
    string line, nline;
    int n, ch, size;
    
    n = 0;
    size = 120;
    line = (string) malloc(size + 1);
    if(line==NULL) return NULL;
    while ((ch = getc(infile)) != '\n' && ch != EOF) {
        if (n == size) {
            size *= 2;
            nline = (string) malloc(size + 1);
            if(nline==NULL) {free(line); return NULL; }
            strncpy(nline, line, n);
            free(line);
            line = nline;
        }
        line[n++] = ch;
    }
    if (n == 0 && ch == EOF) {
        free(line);
        return (NULL);
    }
    line[n] = '\0';
    nline = (string) malloc(n + 1);
    if(nline==NULL) {free(line); return NULL; }
    strcpy(nline, line);
    free(line);
    return (nline);
}

//lists specific commands
static void HelpCommand(void) {
    printf("insert [myg1 | myg2] x y w                  Inserts edge\n");
    printf("delete [myg1 | myg2] x y                    Deletes edge\n");
    printf("printgraph [myg1 | myg2]                    Prints graph\n");
    printf("printdegree [myg1 | myg2]                   Prints degree of each node\n");
    printf("printcomplement [myg1 | myg2]               Prints complement of graph\n");
    printf("eliminatelinks [myg1 | myg2] minW maxW      Deletes all edgs outside minW and maxW\n");
    printf("differentlinks [myg1 | myg2] [myg1 | myg2]  Displays the different links\n");
    printf("commonlinks [myg1 | myg2] [myg1 | myg2]     Displays the common links\n");
    printf("dfs_print [myg1 | myg2] x                   Prints graph in depth first order\n");
    printf("bfs_print [myg1 | myg2] x                   Prints graph in breadth first order\n");
    printf("isconnected [myg1 | myg2]                   Returns if graph is connected\n");
    printf("numofconncomp [myg1 | myg2]                 Returns number of connected components\n");
    printf("help                                        Generates a help message\n");
    printf("quit                                        Quits the program\n");
}

//makes new queue
queueADT NewQueue(void) {
    queueADT queue;
    queue = malloc(sizeof(queueADT));
    if(queue == NULL)
        return NULL;
    queue->head = queue->tail = 0;
    return (queue);
}

//inserts value into queue
void Enqueue(queueADT queue, queueElementT element) {
    if (QueueIsFull(queue)) {
        printf("Enqueue: queue is full");
        return;
    }
    queue->elements[queue->tail] = element;
    queue->tail = (queue->tail + 1)%6;
    
}

//removes value from queue
queueElementT Dequeue(queueADT queue) {
    queueElementT result;
    if (QueueIsEmpty(queue)) {
        printf("Dequeue: queue is empty");
        return NULL;
    }
    result = queue->elements[queue->head];
    queue->head = (queue->head+1)%6;
    return (result);
}

//returns if queue is empty or not
bool QueueIsEmpty(queueADT queue) {
    return (queue->head == queue->tail);
}

//returns if queue is full or not
bool QueueIsFull(queueADT queue) {
    return ((queue->tail + 1)%6 == queue->head);
}

// your other functions
/*
here are some clarifications
*  insert           myg1 3 4  20
insert a new edge 3-4 into myg1 graph with weight of 20. If
this is an undirected graph also insert edge 4-3 with weight
20. If that edge is already in the graph, don't insert
anything...
*  delete           myg1 2 4
delete edge 2-4 from myg1. If this is an undirected graph also
delete edge 4-2. If that edge is not in the graph, don't delete
anything...
*  printgraph       myg1
print graph using the code given...
*  printdegree      myg1
if myg1 is undirected, then simply count the number of
neighbors in the adjacency list for each node and print that
number as the degree of each node..
if the graph is directed, then again you can simply count the
number of neighbors in the adjacency list for each node and
print that number as the out-degree of each node... BUT you
also need to find in-degree. For this, you can check every node
(say node i)and count how many times node i appears in the all
adjacency lists, and print that count as the in-degree for node
i.
*  printcomplement  myg2
First create the complement graph of myg2 as cg, and call
printgraph(cg) then free complement graph cg.
*  eliminatelinks   myg1 minW maxW
check each edge  pe
if (pe->w < minW || pe->w > maxW)  delete that edge
*  differentlinks   myg1 myg2
print edges that are in myg1 but not in myg2
*  commonlinks      myg1  myg2
print edges that are both in myg1 and in myg2
*  dfs_print        myg1 x
print in which order nodes are visited
then for each node print the path from x to that node
*  bfs_print        myg2  x
print in which order nodes are visited
then for each node print the path from x to that node
*  isconnected      myg1
*  numofconncomp    myg2
last two comments isconnected numofconncomp will be performed
if the graph is UNdirected ...
if the graph is directed don't do anything or just print
"Purchase the next version of this program :)"
*/
