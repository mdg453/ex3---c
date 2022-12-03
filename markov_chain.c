#include "markov_chain.h"
#include "linked_list.h"
#include <string.h>
/**
* Get random number between 0 and max_number [0, max_number).
* @param max_number maximal number to return (not including)
* @return Random number
*/
int get_random_number(int max_number)
{
    return rand() % max_number;
}
/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
*/
MarkovNode* get_first_random_node(MarkovChain *markov_chain){
    if(markov_chain == NULL){
        fprintf(stderr, BAD_CHAIN);
        return NULL ;
    }
    if(markov_chain->database->first == NULL){
        fprintf(stderr, BAD_CHAIN);
        return NULL ;
    }
    Node *rand_node = markov_chain->database->first ;
    int ran_num = get_random_number(markov_chain->database->size) ;
    for (int i = 0 ; i < ran_num ; i++) {
        rand_node = rand_node->next ;
    }
    return rand_node->data ;
}


/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr){
    printf("in") ;
    if(state_struct_ptr == NULL){
        fprintf(stderr, BAD_CHAIN);
        return NULL ;
    }
    if(state_struct_ptr->counter_list == NULL){
        fprintf(stderr, BAD_CHAIN);
        return NULL ;
    }

    int biggest = 0;
    MarkovNode *the_node = state_struct_ptr;
    MarkovNode *running_node = state_struct_ptr;
    for (int i = 0 ; i < state_struct_ptr->counter_list_size; i++) {
        //if(running_node->counter_list->frequency > biggest) {
          //  the_node = running_node->counter_list->markov_node ;
           // biggest = the_node->counter_list->frequency ;
       // }
       if (running_node != NULL) {
    //       running_node = running_node->counter_list->markov_node;
       }

    }
    return the_node ;
}

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_random_sequence(MarkovChain *markov_chain,
                                        MarkovNode *first_node, int max_length){
    int i = 0 ;
    MarkovNode *traveler = first_node ;
    printf("in");
    while (i<max_length && traveler->counter_list != NULL){
        traveler = get_next_random_node(first_node) ;
        printf("%s ",traveler->data) ;
    }
}

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free

*/

void free_markov_chain(MarkovChain ** ptr_chain){
    if (ptr_chain == NULL){
        return;
    }
    MarkovChain markovChain = **ptr_chain ;
    if (markovChain.database == NULL) {
        free(*ptr_chain) ;
        ptr_chain = NULL ;
        return;
    }
    if(markovChain.database->first == NULL){
        free(markovChain.database) ;
        free(*ptr_chain) ;
        ptr_chain = NULL ;
        return;
    }
    for(int i = 0 ; i < markovChain.database->size ; i++) {
        free(markovChain.database->first->data->data) ;
        // todo - free (first->data->counterlist)
        free(markovChain.database->first->data) ;
        markovChain.database->first = markovChain.database->first->next ;
    }
    free(markovChain.database) ;
    *ptr_chain = NULL ;

}


/**
 * Add the second markov_node to the counter list of the first markov_node.
 * If already in list, update it's counter value.
 * @param first_node
 * @param second_node
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool add_node_to_counter_list(MarkovNode *first_node, MarkovNode *second_node){
    MarkovNode *traveler = first_node->counter_list->markov_node ;
    for (int i = 0; i < first_node->counter_list_size; ++i) {
        if (traveler->data == second_node->data){
            traveler->counter_list->frequency ++ ;
            return EXIT_SUCCESS ;
        }
    }
    memcpy(first_node->counter_list->markov_node->data , second_node->data,
                                                    strlen(second_node->data)+1);
    if(traveler->counter_list->markov_node == NULL){
        fprintf(stderr,ALLOCATION_ERROR_MASSAGE) ;
        return EXIT_FAILURE ;
    }
    return EXIT_SUCCESS ;
}

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping it in
 * the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr){
    if(markov_chain == NULL){
        fprintf(stderr,"NO DATA IN MARKOV CHAIN") ;
        return NULL ;
    }
    Node *traveler = markov_chain->database->first;
    for (int i = 0; i < markov_chain->database->size; i++) {
        if (traveler->data->data == data_ptr){
            return traveler ;
        }
        traveler = traveler->next ;
    }
    return NULL ;
}

/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */
Node* add_to_database(MarkovChain *markov_chain, char *data_ptr){
    if(markov_chain == NULL){
        fprintf(stderr,"NO DATA IN MARKOV CHAIN") ;
        return NULL ;
    }
    if(markov_chain->database == NULL) {
        fprintf(stderr, "NO DATA IN MARKOV CHAIN");
        return NULL;
    }
    MarkovNode *markovNode = calloc(1, sizeof(MarkovNode)) ;
    markovNode->data = malloc(strlen(data_ptr)+1);
    memcpy(markovNode->data , data_ptr, strlen(data_ptr)+1);
    markovNode->counter_list = NULL;
    markovNode->counter_list_size = 0;
    Node *traveler = get_node_from_database(markov_chain,data_ptr) ;
    if (traveler == NULL){
        if(add(markov_chain->database, markovNode) != 0) {
            fprintf(stderr, ALLOCATION_ERROR_MASSAGE);
            return NULL;
        }
        return markov_chain->database->last;
    }
    else{
        return traveler ;

    }
}






