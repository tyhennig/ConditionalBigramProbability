#ifndef BinaryGramTree_H
#define BinaryGramTree_H
#include <stdio.h>


typedef struct gram_node{
    int count;
    const char* word;
    struct gram_node* left;
    struct gram_node* right;
    struct gram_node* bigrams;
} gram_node;

gram_node* insert_gram(gram_node* root, gram_node* next);
void printUnigrams(gram_node* root, FILE *uni, FILE *bi, FILE *cp);
void printBigrams(FILE *f, FILE *cp, gram_node* root, const char* s, int n);
int compareStrings(const char* root_word, const char* new_word);
void deallocateBigramTree(gram_node* root);
void deallocateUnigramTree(gram_node* root);
void navigateUnigramTree(gram_node* root);
#endif
