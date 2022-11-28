#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"
#include "markov_chain.h"
#define WRONG_INPUT "Usage: int int filepath int"
#define ARGC5 5
#define ARGC4 4
#define ALOC_FAIL “Allocation failure""
#define FILE_FAIL "Error:The given file is invalid.\n"

int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain);

int main(int argc ,char* argv[]){
    if(argc != ARGC5 && argc != ARGC4) {
        fprintf(stderr, WRONG_INPUT) ;
        return EXIT_FAILURE ;
    }
    unsigned int seed = strtol(argv[1], NULL, 10);
    unsigned int tweets_num = strtol(argv[2], NULL, 10);
    unsigned int num_of_words_to_read = 1000 ;
    if(argc == 4) {
        num_of_words_to_read = strtol(argv[4], NULL, 10);;
    }
    char * text = calloc(num_of_words_to_read, sizeof(char)) ;
    if(text == NULL){
        fprintf(stderr,ALLOCATION_ERROR_MASSAGE) ;
        return EXIT_FAILURE ;
    }
    char* input_path = argv[3] ;
    FILE* in = fopen ( input_path, "r") ;
    if (in == NULL) {
        fprintf(stderr,FILE_FAIL ) ;
        return EXIT_FAILURE ;
    }
    fgets(text ,num_of_words_to_read ,in ) ;
    printf("%s",text) ;

    free(text) ;
    fclose(in) ;


}
