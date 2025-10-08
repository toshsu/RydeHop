#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

typedef struct PathNode {
    GraphNode *node;
    double distance;
    GraphNode *previous;
    int visited;
} PathNode;

Graph* create_graph() {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->nodes = create_hash_table();
    graph->edges = create_linked_list();
    graph->next_node_id = 0;
    return graph;
}

GraphNode* graph_add_node(Graph *graph, char *name, double lat, double lon) {
    GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));
    node->id = graph->next_node_id++;
    node->name = strdup(name);
    node->latitude = lat;
    node->longitude = lon;
    node->neighbors = create_linked_list();
    
    char key[20];
    sprintf(key, "%d", node->id);
    hash_insert(graph->nodes, key, node);
    
    return node;
}

void graph_add_edge(Graph *graph, GraphNode *src, GraphNode *dest, double distance) {
    GraphEdge *edge = (GraphEdge*)malloc(sizeof(GraphEdge));
    edge->source = src;
    edge->destination = dest;
    edge->distance = distance;
    edge->time = distance / 30.0; // Assuming 30 km/h average speed
    
    list_insert(src->neighbors, edge);
    list_insert(graph->edges, edge);
}

static double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    double dlat = (lat2 - lat1) * M_PI / 180.0;
    double dlon = (lon2 - lon1) * M_PI / 180.0;
    
    double a = sin(dlat/2) * sin(dlat/2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dlon/2) * sin(dlon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return 6371 * c; // Earth radius in km
}

PathNode* find_min_distance_node(LinkedList *nodes) {
    ListNode *current = nodes->head;
    PathNode *min_node = NULL;
    double min_distance = DBL_MAX;
    
    while (current != NULL) {
        PathNode *pnode = (PathNode*)current->data;
        if (!pnode->visited && pnode->distance < min_distance) {
            min_distance = pnode->distance;
            min_node = pnode;
        }
        current = current->next;
    }
    return min_node;
}

LinkedList* find_shortest_path(Graph *graph, GraphNode *start, GraphNode *end) {
    HashTable *distances = create_hash_table();
    LinkedList *unvisited = create_linked_list();
    
    // Initialize distances
    for (int i = 0; i < TABLE_SIZE; i++) {
        ListNode *current = graph->nodes->buckets[i]->head;
        while (current != NULL) {
            HashEntry *entry = (HashEntry*)current->data;
            GraphNode *node = (GraphNode*)entry->data;
            
            PathNode *pnode = (PathNode*)malloc(sizeof(PathNode));
            pnode->node = node;
            pnode->visited = 0;
            pnode->previous = NULL;
            
            if (node == start) {
                pnode->distance = 0.0;
            } else {
                pnode->distance = DBL_MAX;
            }
            
            char key[20];
            sprintf(key, "%d", node->id);
            hash_insert(distances, key, pnode);
            list_insert(unvisited, pnode);
            
            current = current->next;
        }
    }
    
    // Dijkstra's algorithm without heap
    while (unvisited->size > 0) {
        PathNode *current = find_min_distance_node(unvisited);
        if (current == NULL || current->distance == DBL_MAX) break;
        
        current->visited = 1;
        list_remove(unvisited, current, NULL); // Simple remove without compare
        
        if (current->node == end) break;
        
        // Update neighbors
        ListNode *edge_node = current->node->neighbors->head;
        while (edge_node != NULL) {
            GraphEdge *edge = (GraphEdge*)edge_node->data;
            GraphNode *neighbor = edge->destination;
            
            char key[20];
            sprintf(key, "%d", neighbor->id);
            PathNode *neighbor_pnode = (PathNode*)hash_get(distances, key);
            
            if (!neighbor_pnode->visited) {
                double new_distance = current->distance + edge->distance;
                if (new_distance < neighbor_pnode->distance) {
                    neighbor_pnode->distance = new_distance;
                    neighbor_pnode->previous = current->node;
                }
            }
            edge_node = edge_node->next;
        }
    }
    
    // Build path
    LinkedList *path = create_linked_list();
    GraphNode *current_node = end;
    while (current_node != NULL) {
        list_insert(path, current_node);
        
        char key[20];
        sprintf(key, "%d", current_node->id);
        PathNode *pnode = (PathNode*)hash_get(distances, key);
        current_node = pnode->previous;
    }
    
    // Cleanup
    free_hash_table(distances);
    free_linked_list(unvisited);
    
    return path;
}

void free_graph(Graph *graph) {
    free_hash_table(graph->nodes);
    
    ListNode *current = graph->edges->head;
    while (current != NULL) {
        free(current->data);
        current = current->next;
    }
    free_linked_list(graph->edges);
    
    free(graph);
}