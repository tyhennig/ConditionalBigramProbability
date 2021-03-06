/******************************************************************************
Written by: Tyler Hennig
Title: Bigram Conditional Probability Calculator
For: Operating Systems Homework 2
Last Update: 4/4/2021

*******************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"




//function to copy a node
gram_node* copyGram(gram_node* g){ 
    
    gram_node* newG = malloc(sizeof(gram_node));
    
    const char* s = g->word;
    
    
    newG->word = s;
    newG->count = 1;
    newG->left = NULL;
    newG->right = NULL;
    newG->bigrams = NULL;
    
    return newG;
    
}


int main(int argc, char *argv[])
{

    double times[argc];
for(int file_index = 1; argv[file_index]; file_index++){

	FILE *fp;
	FILE *uni;
	FILE *bi;
	FILE *cp;
    char* str = malloc(sizeof(char) * 30);
    clock_t begin = clock();
    int str_size = 0;
    int started = 0;
    int char_count;
    int file_char_count;
    fp = fopen(argv[file_index], "r");
    
    gram_node* root = NULL; //pointers of current node and previous node
    gram_node* prev = NULL;
    gram_node* next = NULL;
    

    //copy the argv[1] into a new variable called file_name
    char* file_name;
    file_char_count = 0;
    for(int i = 0; argv[file_index][i]; i++){
        file_char_count = i;
    }
    file_name = malloc(sizeof(char) * (file_char_count));
    for(int i = 0; argv[file_index][i]; i++){
        file_name[i] = argv[file_index][i];
        
    }
    
    //while not end of file, scan for white space separated words. Only include a-zA-Z and '
    while(fscanf(fp, " %29[a-zA-Z']%*[^a-zA-Z]", str) != EOF){
    	
        printf("reading word %s...\n", str);
        char_count = 0;

        for(int i = 0; str[i]; i++){
            char_count = i;
        }
        
        
        char* new_word = malloc(sizeof(char) * (char_count+2)); //include space for null character
        //convert read word to lower case
        for(int i = 0; str[i]; i++){
            str[i] = tolower(str[i]);
            new_word[i] = str[i];
        }
        new_word[char_count + 1] = '\000'; //assign null character
                
        //check if tree has started, if not start. Otherwise, insert gram into tree.
        //Insert the current unigram into the previous gram_node's bigram tree;
        if(!started){
            printf("starting...\n");
            root = insert_gram(NULL, new_word);
            next = root;
            started = 1;
        }else{
            next = insert_gram(root, new_word);
            if(prev->bigrams == NULL){
                prev->bigrams = copyGram(next); //make a copy of the gram to be stored in the prev's bigram tree
            } else{
                insert_gram(prev->bigrams, new_word);
            }
        }
        
        prev = next;
        
    }
    
    fclose(fp);
    
    //change file name to .uni, .bi and .cp
    file_name[file_char_count] = 'i';
    file_name[file_char_count-1] = 'n';
    file_name[file_char_count-2] = 'u';
    uni = fopen(file_name, "w+");
    
    file_name[file_char_count] = '\000';
    file_name[file_char_count-1] = 'i';
    file_name[file_char_count-2] = 'b';
    bi = fopen(file_name, "w+");
    
    file_name[file_char_count] = '\000';
    file_name[file_char_count-1] = 'p';
    file_name[file_char_count-2] = 'c';
    cp = fopen(file_name, "w+");
    
    printf("Printing Unigrams!!\n");
    printUnigrams(root, uni, bi, cp);
    printf("Printing Bigrams!!\n");
    //navigateUnigramTree(root, bi, cp);
    fclose(uni);
    fclose(bi);
    fclose(cp);

    file_name[file_char_count-3] = '\000';
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    times[file_index-1] = time_spent;
    
    //free the used tree memory
    navigateUnigramTree(root);
    deallocateUnigramTree(root);
    
    free(file_name);
    
  }  
  for(int i = 0; times[i]; i++){
    printf("Time taken: %f seconds of CPU time for file %s\n\n", times[i], argv[i+1]);
  }
}
