#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"
#include "markov_chain.h"
#define WRONG_INPUT "Usage: int int filepath int"
#define ARGC5 5
#define ARGC4 4
#define FILE_FAIL "Error:The given file is invalid.\n"


void print_markov_chain(struct MarkovChain* markov_chain)
{
    printf("MarkovChain:\n");
    LinkedList* list = markov_chain->database;
    Node* cur = list->first;
    for (int i = 0; i < list->size; i++)
    {
        printf("%d.\t%s : [ ", i, cur->data->data);
        struct NextNodeCounter* arr = cur->data->counter_list;
        for (int j = 0; j < cur->data->counter_list_size; j++)
        {
            printf("{%s : %d} ", arr[j].markov_node.data, arr[j].frequency);
        }
        printf("]\n");
        cur = cur->next;
    }
}

int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain);

int main(int argc ,char* argv[]){
    if(argc != ARGC5 && argc != ARGC4) {
        fprintf(stderr, WRONG_INPUT) ;
        return EXIT_FAILURE ;
    }
    unsigned int seed = strtol(argv[1], NULL, 10);
    unsigned int tweets_num = strtol(argv[2], NULL, 10);
    unsigned int num_of_words_to_read = 1000 ;
    int num_of_Chars_to_read = 1000 ;
    if(argc == 4) {
        num_of_words_to_read = strtol(argv[4], NULL, 10);;
    }
    char * text = calloc(num_of_words_to_read, sizeof(char)) ;
    if(text == NULL){
        fprintf(stderr,ALLOCATION_ERROR_MASSAGE) ;
        return EXIT_FAILURE ;
    }
    char s_in[1000] = {0};
    char* input_path = argv[3] ;
    FILE* in = fopen ( input_path, "r") ;
    if (in == NULL) {
        fprintf(stderr,FILE_FAIL ) ;
        return EXIT_FAILURE ;
    }
    while(fgets(text ,num_of_Chars_to_read,in ) != NULL){
        printf("%s",s_in) ;
    }
    free(text) ;
    fclose(in) ;


}
