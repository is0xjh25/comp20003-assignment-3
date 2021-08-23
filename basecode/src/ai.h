#ifndef __AI__
#define __AI__

#include <stdint.h>
#include <unistd.h>
#include "hashtable.h"
#include "utils.h"

void initialize_ai();
void find_solution(state_t* init_state);
void free_memory(HashTable* table, position_s* selected_peg, node_t** used_nodes, int used_nodes_count);
node_t** add_used_nodes (node_t* new_node, node_t** used_nodes, int* used_nodes_count);



#endif
