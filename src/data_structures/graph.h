#ifndef GRAPH_H
#define GRAPH_H

#include "linked_list.h"
#include "hash_table.h"

typedef struct GraphNode {
    int id;
    char *name;
    double latitude;
    double longitude;
    LinkedList *neighbors;
} GraphNode;

typedef struct GraphEdge {
    GraphNode *source;
    GraphNode *destination;
    double distance;
    double time;
} GraphEdge;

typedef struct {
    HashTable *nodes;
    LinkedList *edges;
    int next_node_id;
} Graph;

Graph* create_graph();
GraphNode* graph_add_node(Graph *graph, char *name, double lat, double lon);
void graph_add_edge(Graph *graph, GraphNode *src, GraphNode *dest, double distance);
LinkedList* find_shortest_path(Graph *graph, GraphNode *start, GraphNode *end);
void free_graph(Graph *graph);

#endif