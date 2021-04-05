#include "bst.h"
#include <stdio.h>
#include <stdlib.h>



int isOpen = 0;


gram_node* insert_gram(gram_node* root, char* next){
	
    if(root == NULL){//initialize the first root of the tree
        root = malloc(sizeof(gram_node));
        root->word = next;
        root->count = 1;
        root->right = NULL;
        root->left = NULL;
        root->bigrams = NULL;
        return root;
    } else{
    	//printf("Next word: %s... Root word: %s\n", next, root->word);
        int result = compareStrings(root->word, next);//check if word is same or should go right or left
        //printf("result was: %d\n", result);
        if(result == 3){	//word is same
           root->count++;
           //printf("%s count is now %d\n", root->word, root->count);
           return root;
        }else if(result == 1){	//word is less than root
            //insert left
            if(root->left == NULL){	//if the left side is null insert it there, other wise navigate further
                gram_node* new_gram = malloc(sizeof(gram_node));
                new_gram->word = next;
                new_gram->left = NULL;
                new_gram->right = NULL;
                new_gram->bigrams = NULL;
                new_gram->count = 1;
                root->left = new_gram;
                return root->left;
            } else{
                insert_gram(root->left, next);
            }
        }else if(result == 0){
            //insert right
            if(root->right == NULL){
                gram_node* new_gram = malloc(sizeof(gram_node));
                new_gram->word = next;
                new_gram->left = NULL;
                new_gram->right = NULL;
                new_gram->bigrams = NULL;
                new_gram->count = 1;
                root->right = new_gram;
                return root->right;
            } else{
                insert_gram(root->right, next);
            }
        }else{
                fprintf(stderr, "Error comparing strings");
        }
        
    }
    
}


//prints a given unigram's bigram tree to the given file.
void printBigrams(FILE *f, FILE *cp, gram_node* root, const char* s, int n){
    
    float p;
    p = (float)root->count / (float)n; //calculate probability
    
    fprintf(f, "%s %s count: %d \n", s, root->word, root->count);
    fprintf(cp, "P(%s | %s) = %8.4f\n", root->word, s, p);
    
    //check both children of bigram node, navigate there if not null.
    if(root->left != NULL){
        printBigrams(f, cp, root->left, s, n);	
    }
    if(root->right != NULL){
        printBigrams(f, cp, root->right, s, n);
    }
    
    //free(root);

}

void printUnigrams(gram_node* root, FILE *uni, FILE *bi, FILE *cp){
    
    fprintf(uni, "%s count: %d\n", root->word, root->count);
    
    if(root->bigrams != NULL){
        printBigrams(bi, cp, root->bigrams, root->word, root->count);
    }
   
    if(root->left != NULL){
        printUnigrams(root->left, uni, bi, cp);
    }

    if(root->right != NULL){
        printUnigrams(root->right, uni, bi, cp);
    }
    //free(root);
}

int compareStrings(const char* root_word, const char* new_word){ //return 1 if left, 0 if right, 3 if equal
    for(int i = 0; i < 29; i++){//30 is the max size a string could be in this context
        
        
        if(root_word[i] > new_word[i]){
            return 1;
        } else if(root_word[i] < new_word[i]){
            return 0;
        } else if(root_word[i] == '\000' && new_word[i] == '\000'){//prevent short words, "a", from being compared all 30 times
            return 3;
        }
    }
    return 3;
}

void navigateUnigramTree(gram_node* root){
	if(root->left != NULL){
		navigateUnigramTree(root->left);
	}
	
	if(root->right != NULL){
		navigateUnigramTree(root->right);
	}
	if(root->bigrams != NULL){
		deallocateBigramTree(root->bigrams);
	}
}

void deallocateBigramTree(gram_node* root){
	
	if(root->left != NULL){
		deallocateBigramTree(root->left);
	}
	if(root->right != NULL){
		deallocateBigramTree(root->right);
	}
	
	free(root);
}
void deallocateUnigramTree(gram_node* root){
	if(root->left != NULL){
		deallocateUnigramTree(root->left);
	}
	if(root->right != NULL){
		deallocateUnigramTree(root->right);
	}
	
	free(root);
	
}

