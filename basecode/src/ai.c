#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

#include "utils.h"
#include "stack.h"
#include "hashtable.h"
#include "ai.h"


void copy_state(state_t* dst, state_t* src){

	// Copy field
	memcpy(dst->field, src->field, SIZE*SIZE*sizeof(int8_t));

	dst->cursor = src->cursor;
	dst->selected = src->selected;
}

/**
 * Saves the path up to the node as the best solution found so far
*/
void save_solution(node_t* solution_node){
	node_t* n = solution_node;
	while( n->parent != NULL ){
		copy_state(&(solution[n->depth]), &(n->state));
		solution_moves[n->depth - 1] = n->move;

		n = n->parent;
	}
	solution_size = solution_node->depth;
}


node_t* create_init_node( state_t* init_state ){
	node_t* new_n = (node_t*)malloc(sizeof(node_t));
	new_n->parent = NULL;
	new_n->depth = 0;
	copy_state(&(new_n->state), init_state);
	return new_n;
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
node_t* applyAction(node_t* n, position_s* selected_peg, move_t action ) {

    node_t* new_node = NULL;

	// FILL IN MISSING CODE
	new_node = (node_t*)malloc(sizeof(node_t));
	assert(new_node);

	new_node->parent = n;
	new_node->depth = n->depth + 1;
	new_node->move = action;
	new_node->state = n->state;
	new_node->state.cursor = *selected_peg;

    execute_move_t(&(new_node->state), &(new_node->state.cursor), action);

	return new_node;
}

/**
 * Find a solution path as per algorithm description in the handout
*/
void find_solution(state_t* init_state) {

	HashTable table;

	// Choose initial capacity of PRIME NUMBER
	// Specify the size of the keys and values you want to store once
	ht_setup( &table, sizeof(int8_t) * SIZE * SIZE, sizeof(int8_t) * SIZE * SIZE, 16769023);

	// Initialize Stack
	initialize_stack();

	// Add the initial node
	node_t* n = create_init_node(init_state);

	// Temporary position_s for recording current positions
	position_s* selected_peg = (position_s*)malloc(sizeof(position_s));
	assert(selected_peg);

	// An array contains node_t address for freeing memory when program is finish
	node_t** used_nodes = NULL;
	int used_nodes_count = 0;

	node_t* new_node = NULL;

	int remaining_pegs = num_pegs(&(n->state));
	int i,j,k;

	// FILL IN THE GRAPH ALGORITHM
	stack_push(n);

	while (is_stack_empty() != 1) {

		n = stack_top(stack_top_idx);
		stack_pop();
		expanded_nodes ++;

		// Add node into array
		used_nodes = add_used_nodes (n, used_nodes, &used_nodes_count);

		if (num_pegs(&(n->state)) < remaining_pegs) {
			save_solution(n);
			remaining_pegs = num_pegs(&(n->state));
		}

		for (i = 0; i < SIZE; i++) {

			for (j = 0; j < SIZE; j++) {

				// Left, right, up and down
				for (k = left; k <= down; k++) {

					// Form i and j as the struct position_s
					selected_peg->x = i;
					selected_peg->y = j;

					if (can_apply((&(n->state)), selected_peg, k)) {

						new_node = applyAction(n, selected_peg, k);
						generated_nodes++;

						// GAME OVER
						if (won(&(new_node->state))) {
							save_solution(new_node);
							remaining_pegs = num_pegs(&(new_node->state));
							used_nodes = add_used_nodes (new_node, used_nodes, &used_nodes_count);
							free_memory(&table, selected_peg, used_nodes, used_nodes_count);
							return;
						}

						// Check whether the state is duplicate by using hashtable
						if (ht_contains(&table, &(new_node->state.field)) == HT_NOT_FOUND) {
							// It is a new node, so add it into hashtable
							ht_insert(&table, &(new_node->state.field), &(new_node->state.field));
							// DFS strategy
							stack_push(new_node);
						} else {
							// If the node is duplicate, it needs to be dumped now
							used_nodes = add_used_nodes (new_node, used_nodes, &used_nodes_count);
						}
					}
				}
			}
		}
		// GAME OVER
		if (expanded_nodes >= budget) {
			free_memory(&table, selected_peg, used_nodes, used_nodes_count);
			return;
		}
	}
	// GAME OVER (All possible outcomes discoverd still under budget and can't win)
	free_memory(&table, selected_peg, used_nodes, used_nodes_count);
}

/**
 * Add a new node into an array, it records the used nodes which need to be freed
*/
node_t** add_used_nodes (node_t* new_node, node_t** used_nodes, int* used_nodes_count) {

	// Create array or resize array
	if (used_nodes == NULL) {
		used_nodes = (node_t**)malloc(sizeof(node_t*));
		(*used_nodes_count) ++;
		assert(used_nodes);
	} else {
		(*used_nodes_count) ++;
		used_nodes = (node_t**)realloc(used_nodes, sizeof(node_t*) * (*used_nodes_count));
		assert(used_nodes);
	}

	used_nodes[(*used_nodes_count) - 1] = new_node;
	return used_nodes;
}

/**
 * Free all memory including a hashtable, used nodes, a stack and a struct of position_s
*/
void free_memory(HashTable* table, position_s* selected_peg, node_t** used_nodes, int used_nodes_count) {

	free_stack();
	free(selected_peg);
	ht_destroy(table);

	// Free used_nodes array
	int i = 0;
	for (i = 0; i < used_nodes_count; i++) {
		free(used_nodes[i]);
	}
	free(used_nodes);
}
