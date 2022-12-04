#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"
#include "markov_chain.h"
#define WRONG_INPUT "Usage: int int filepath int"
#define ARGC5 5
#define ARGC4 4
#define FILE_FAIL "Error:The given file is invalid.\n"
#define NUM_OF_CHARS  100000000
#define NUM1000 1000


int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain){
    char  text[NUM1000];
    LinkedList *linkedlist = malloc(sizeof(LinkedList)) ;
    if(linkedlist == NULL){
        fprintf(stderr,ALLOCATION_ERROR_MASSAGE) ;
        return EXIT_FAILURE ;
    }
    markov_chain->database = linkedlist ;
    char *token;
    MarkovNode * previus_word = NULL;
    Node * current_word ;
    while(fgets(text ,NUM_OF_CHARS,fp ) != NULL && words_to_read) {
        text[strcspn(text, "\n")] = '\0' ;
        token = strtok(text, " \r\n");
        while(token != NULL && words_to_read > 0) {
            current_word = add_to_database(markov_chain, token) ;
            add_node_to_counter_list(previus_word, current_word->data);
            previus_word = current_word->data;
            token = strtok(NULL, " \r\n");
            words_to_read--  ;
        }
    }
    return EXIT_SUCCESS ;
}


int main(int argc ,char* argv[]){
    if(argc < ARGC4) {
        fprintf(stderr, WRONG_INPUT) ;
        return EXIT_FAILURE ;
    }
    unsigned int seed = strtol(argv[1], NULL, 10);
    long int tweets_num = strtol(argv[2], NULL, 10);
    unsigned int num_of_chars_to_read = NUM_OF_CHARS ;
    srand(seed);
    if(argc == ARGC5) {
        num_of_chars_to_read = strtol(argv[4], NULL, 10);;
    }
    char* input_path = argv[3] ;
    MarkovChain * base_root = calloc(1, sizeof (MarkovChain));
    FILE* in = fopen ( input_path, "r") ;
    if (in == NULL) {
        fprintf(stderr,FILE_FAIL ) ;
        return EXIT_FAILURE ;
    }
    fill_database(in, num_of_chars_to_read,base_root);
    generate_random_sequence(base_root,
                             base_root->database->first->data,tweets_num);
    MarkovChain **point_to_base = &base_root ;
    //printf("\n%d",base_root->database->size);
    free_markov_chain(point_to_base) ;
    fclose(in) ;

}
