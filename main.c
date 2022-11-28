#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"
#include "markov_chain.h"


int main(int argc ,char* argv[]){
    if(argc != 2)
    {
       return EXIT_FAILURE ;
    }
    char* input_path = argv[1] ;
    FILE* in = fopen ( input_path, "r") ;
    if (in == NULL)
    {
        fprintf(stderr,"The given file is invalid.\n" ) ;
        return EXIT_FAILURE ;
    }


}
