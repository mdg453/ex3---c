#include "markov_chain.h"


MarkovNode* get_first_random_node(MarkovChain *markov_chain);


MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr);


void generate_random_sequence(MarkovChain *markov_chain, MarkovNode *first_node, int max_length);


void free_markov_chain(MarkovChain ** ptr_chain);


bool add_node_to_counter_list(MarkovNode *first_node, MarkovNode *second_node);


Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr);


Node* add_to_database(MarkovChain *markov_chain, char *data_ptr);

/**
* Get random number between 0 and max_number [0, max_number).
* @param max_number maximal number to return (not including)
* @return Random number
*/
int get_random_number(int max_number)
{
    return rand() % max_number;
}
