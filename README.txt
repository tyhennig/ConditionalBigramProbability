This program counts the unigrams, bigrams, and bigram probabilities of a given text file.

To compile, open your terminal to the location of the .c files file and type: cc main.c bst.c -lm
The -lm option ensures the compiler links to the necessary libraries included by the code.

To run the program, type ./a.out "name of the file to process"

Example: ./a.out TomSawyer.txt

*NOTE*
I encountered a very strange bug during this process which I have not been able to solve:
when using files downloaded from the suggested website (gutenberg project) it is unable to fscanf past the first line.

*FIX*
However, if the user makes any changes and saves the file, the program will function normally.
Even if it is deleting and retyping a single letter. I suspect it has something to do with the 
file format containing unreadable characters and when the file is saved, something "resets".
 
