This program counts the unigrams, bigrams, and bigram probabilities of a given text file(s).

Something I enjoy about this code is the fact that the insertion code and node structs for both the unigrams and bigrams are the same.
While I could have saved a small amount of memory by creating a different struct (because bigrams don't need to keep track of their bigrams), I decided that the simplicity and elegance of the code was worth the sacrifice. When a new word is read, we insert it into the unigram binary search tree and then cache it in a "prev" pointer. After reading and inserting the next word, we also insert it into the previous node's binary tree. This creates a BST within a BST and is very easy to traverse every node for later deallocation.

To compile, open your terminal to the location of the .c files file and type: cc hw2.c bst.c -lm
The -lm option ensures the compiler links to the necessary libraries included by the code.

To run the program, type ./a.out "name of the files to process"

Example: ./a.out TomSawyer.txt GildedAge.txt HuckleBerry.txt

*NOTE*
I encountered a very strange bug during this process which I have not been able to solve:
when using files downloaded from the suggested website (gutenberg project) it is unable to scan past the first line.

*FIX*
If the user makes any changes and saves the file, the program will function normally.
Even if it is deleting and retyping a single letter. I suspect it has something to do with the 
file format containing unreadable characters and when the file is saved, something "resets".

Please email me at tyler.hennig@students.tamuk.edu with any questions.
 
